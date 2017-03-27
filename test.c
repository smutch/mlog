#include <unistd.h>
#include "mlog.h"

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);

  const char *name = "Sport!";

  init_mlog(MPI_COMM_WORLD, stdout, stdout, stderr);

  mlog(MLOG_MESG, "G'day %s", name);
  mlog(MLOG_OPEN | MLOG_TIMERSTART, "Starting timer 1:");
  mlog(MLOG_CONT, "This log message won't start a new line...");
  mlog(MLOG_MESG | MLOG_TIMERSTART, "...Timers can also be nested, so let's start timer 2.");
  mlog(MLOG_CLOSE | MLOG_TIMERSTOP, "...and end it.  That was quick!");
  mlog(MLOG_MESG, "Now wait for 1 second.");
  sleep(1);
  mlog(MLOG_TIMERSTOP | MLOG_CONT, "...and check timer 1...");
  mlog(MLOG_MESG, "Excellent!");

  mlog(MLOG_NOINDENT, "<WARNING> An error is coming...");
  mlog_error("Don't worry - this is just a test.");

  MPI_Finalize();

  return 0;
}
