#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int count = 0;

void signal_handler(int signal) {
  count++;
}

int main(int argc, char **argv) {
  struct sigaction sa;
  sa.sa_handler = &signal_handler;
  sa.sa_flags = 0;
  sigfillset(&sa.sa_mask);
  sa.sa_restorer = NULL;

  if(sigaction(SIGINT, &sa, NULL) < 0) {
    printf("Failed to install signal handler\n");
    return 1;
  }
  while(count < 10) {
    printf("Waiting for SIGINT. Count: %d\n", count);
    sleep(10);
  }

  printf("Enough SIGINTs, exiting\n");
  return 0;
}
