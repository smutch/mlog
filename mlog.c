#define _MAIN
#include <stdlib.h>
#include <stdarg.h>
#include "mlog.h"

void init_mlog(MPI_Comm comm,
    FILE *file_info,
    FILE *file_warning,
    FILE *file_error)
{
  for(int ii = 0; ii < MLOG_NTIMERS; ii++)
    _mlog.timer_on[ii] = false;

  _mlog.file_info    = file_info;
  _mlog.file_warning = file_warning;
  _mlog.file_error   = file_error;

  _mlog.comm         = comm;
}


void _mlog_error(const char *fmt,
    const char *file_name,
    const char *func_name,
    int lineno,
    ...)
{
  int rank;

  MPI_Comm_rank(_mlog.comm, &rank);
  fprintf(_mlog.file_error, "<ERROR> rank %d [%s->%s +%d]: ", rank, func_name, file_name, lineno);

  va_list args;
  va_start(args, lineno);
  vfprintf(_mlog.file_error, fmt, args);
  va_end(args);

  fprintf(_mlog.file_error, "\n");
}


void _mlog_info(const char *fmt,
    int flags,
    const char *file_name,
    const char *func_name,
    int lineno,
    ...)
{
  int   rank;

  MPI_Comm_rank(_mlog.comm, &rank);
  FILE *fd = _mlog.file_info;

  if ((rank != 0) && ((flags & MLOG_ALLRANKS) != MLOG_ALLRANKS))
    return;

  if ((flags & MLOG_CLOSE) == MLOG_CLOSE)
  {
    _mlog.indent--;
    if (_mlog.indent < 0)
      _mlog.indent = 0;
  }

  if ((flags & MLOG_CONT) != MLOG_CONT)
  {
    fprintf(fd, "\n");
    if ((flags & MLOG_NOINDENT) != MLOG_NOINDENT)
      for(int ii = 0; ii < _mlog.indent; ii++)
        fprintf(fd, "    ");
  }
  
  if ((flags & MLOG_ALLRANKS) == MLOG_ALLRANKS)
      fprintf(fd, "rank %d: ", rank);

  if ((flags & MLOG_LOCATION) == MLOG_LOCATION)
    fprintf(fd, "[%s->%s +%d] ", func_name, file_name, lineno);

  va_list args;
  va_start(args, lineno);
  vfprintf(fd, fmt, args);
  va_end(args);

  if((flags & MLOG_TIMERSTOP) == MLOG_TIMERSTOP)
  {
    bool           success = false;
    struct timeval now, result;

    gettimeofday(&now, NULL);

    for(int ii = MLOG_NTIMERS - 1; ii >= 0; ii--)
      if(_mlog.timer_on[ii])
      {
        timersub(&now, &_mlog.timer[ii], &result);
        _mlog.timer_on[ii] = false;
        success            = true;
        break;
      }
    if(success)
      fprintf(fd, " (%ld.%06ld s)", (long int)result.tv_sec, (long int)result.tv_usec);
    else
      mlog_error("Failed to find open timer to close.");
  }

  if ((flags & MLOG_OPEN) == MLOG_OPEN)
    _mlog.indent++;

  if ((flags & MLOG_TIMERSTART) == MLOG_TIMERSTART)
  {
    // find the first empty timer and record the current time
    bool success = false;
    for(int ii = 0; ii < MLOG_NTIMERS; ii++)
      if(!_mlog.timer_on[ii])
      {
        gettimeofday(&_mlog.timer[ii], NULL);
        _mlog.timer_on[ii] = true;
        success            = true;
        break;
      }

    if(!success)
      mlog_error("Maximum timer depth exceeded.");
  }
}
