#ifndef _MLOG_H
#define _MLOG_H
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#define MLOG_MESG (unsigned int)1
#define MLOG_OPEN (unsigned int)2
#define MLOG_CLOSE (unsigned int)4
#define MLOG_CONT (unsigned int)8
#define MLOG_TIMERSTART (unsigned int)16
#define MLOG_TIMERSTOP (unsigned int)32
#define MLOG_LOCATION (unsigned int)64
#define MLOG_ALLRANKS (unsigned int)128
#define MLOG_NOINDENT (unsigned int)256
#define MLOG_FLUSH (unsigned int)512

#define MLOG_NTIMERS 3

typedef struct mlog_t
{
  struct timeval timer[MLOG_NTIMERS];
  bool timer_on[MLOG_NTIMERS];
  MPI_Comm comm;
  FILE* file_info;
  FILE* file_warning;
  FILE* file_error;
  int indent;
} mlog_t;

#ifndef _MAIN
extern mlog_t _mlog;
#else
mlog_t _mlog;
#endif

#ifdef __cplusplus
extern "C"
{
#endif
  void init_mlog(MPI_Comm comm, FILE* file_info, FILE* file_warning, FILE* file_error);

#define mlog_error(fmt, ...) _mlog_error(fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
  void _mlog_error(const char* fmt, const char* file_name, const char* func_name, int lineno, ...);

#define mlog(fmt, flags, ...) _mlog_info(fmt, flags, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
  void _mlog_info(const char* fmt, int flags, const char* file_name, const char* func_name, int lineno, ...);
#ifdef __cplusplus
}
#endif
#endif
