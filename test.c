#include "mlog.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);

  const char* name = "Sport!";

  init_mlog(MPI_COMM_WORLD, stdout, stdout, stderr);

  mlog("G'day %s", MLOG_MESG, name);
  mlog("Starting timer 1:", MLOG_OPEN | MLOG_TIMERSTART);
  mlog("This log message won't start a new line...", MLOG_CONT);
  mlog("...Timers can also be nested, so let's start timer 2.", MLOG_MESG | MLOG_TIMERSTART);
  mlog("...and end it.  That was quick!", MLOG_CLOSE | MLOG_TIMERSTOP);
  mlog("Now wait for 1 second.", MLOG_MESG);
  sleep(1);
  mlog("...and check timer 1...", MLOG_TIMERSTOP | MLOG_CONT);
  mlog("Excellent!", MLOG_MESG);

  mlog("<WARNING> An error is coming...", MLOG_NOINDENT);
  mlog_error("Don't worry - this is just a test.");

  MPI_Finalize();

  return 0;
}
