#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv) {
  sigset_t signalset;
  sigset_t originalset;

  sigemptyset(&signalset);
  sigaddset(&signalset, SIGINT);

  if(sigprocmask(SIG_BLOCK, &signalset, &originalset) < 0) {
    printf("Problem blocking SIGINT\n");
    return 1;
  }
  printf("SIGINT now blocked. Try CTRL+C\n");
  sleep(10);

  if(sigprocmask(SIG_UNBLOCK, &signalset, &originalset) < 0) {
    printf("Problem unblock SIGINT\n");
    return 1;
  }
  printf("Done sleeping. SIGINT unblocked\n");
  return 0;
}
