#include <sys/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <mpi.h>

#define MLOG_MESG 1
#define MLOG_OPEN 2
#define MLOG_CLOSE 4
#define MLOG_CONT 8
#define MLOG_TIMERSTART 16
#define MLOG_TIMERSTOP 32
#define MLOG_LOCATION 64
#define MLOG_ALLRANKS 128
#define MLOG_NOINDENT 256

#define MLOG_NTIMERS 3

typedef struct mlog_t {
  struct timeval timer[MLOG_NTIMERS];
  bool timer_on[MLOG_NTIMERS];
  MPI_Comm comm;
  FILE *file_info;
  FILE *file_warning;
  FILE *file_error;
  bool cont;
  int indent;
} mlog_t;

#ifndef _MAIN
extern mlog_t _mlog;
#else
mlog_t        _mlog;
#endif

void init_mlog(MPI_Comm comm, FILE *file_info, FILE *file_warning, FILE *file_error);

#define mlog_error(fmt, ...) _mlog_error(fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__)
void _mlog_error(const char *fmt, const char *file_name, const char *func_name, int lineno, ...);

#define mlog(fmt, flags, ...) _mlog_info(fmt, flags, __FILE__, __func__, __LINE__, ## __VA_ARGS__)
void _mlog_info(const char *fmt, int flags, const char *file_name, const char *func_name, int lineno, ...);
