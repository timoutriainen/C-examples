#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

static int childrenCount = 0;

void myHandler(int signum) {
  childrenCount--;
  printf("myHandler() - child has died, %d remaining\n", childrenCount);
}

int childact(int nro) {
  usleep(1000);
  int sleepTime = 0;
  srand(time(NULL));
  sleepTime = rand() % 10 + 2;
  printf("I am child %d and I'll sleep for %d\n",nro,sleepTime);
  sleep(sleepTime);
  return 0;
}

int count = 0;

int main(int argc, char** argv) {
  struct sigaction sa;
  sa.sa_handler = &myHandler;

  sigfillset(&sa.sa_mask);
  sa.sa_flags = 0;

  if(sigaction(SIGCHLD, &sa, NULL) < 0) {
    printf("Failed to install signal handler\n");
    return 1;
  }

  pid_t pid1 = 0;
  for(int i=0; i<10; i++) {
    pid1 = fork();
    if(pid1 < 0) {
      printf("Error!\n");
      exit(1);
    }
    if(pid1 == 0) {
      childact(i);
      exit(0);
    }
    childrenCount++;
    sleep(1);
  }
  printf("childrens: %d\n", childrenCount);
  int childpid = 0, status = 0, previousChildrenCount = childrenCount;
  while (childrenCount != 0) {
    if(previousChildrenCount != childrenCount) {
      printf("A child has died!!! \n");
      childpid = wait(&status);
      printf("Child had pid %d and status %d\n",childpid,status);
      previousChildrenCount = childrenCount;
    }		
    sleep(1);
  }


  printf("main() - exiting\n");
  return 0;

}
