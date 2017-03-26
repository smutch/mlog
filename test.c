#include <unistd.h>
#include "mlog.h"

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);

  const char *name = "simon";

  init_mlog(MPI_COMM_WORLD, stdout, stdout, stderr);

  mlog(MLOG_MSG, "hello %s", name);
  mlog(MLOG_OPEN|MLOG_TIMERSTART, "hello:");
  mlog(MLOG_CONT, "simon");
  mlog(MLOG_MSG|MLOG_TIMERSTART, "is the best!");
  mlog(MLOG_CLOSE|MLOG_TIMERSTOP, "...boom!");
  sleep(1);
  mlog(MLOG_TIMERSTOP, "excellent...");

  mlog(MLOG_NOINDENT, "<WARNING> Error is coming...");
  mlog_error("Test");

  MPI_Finalize();

  return 0;
}
