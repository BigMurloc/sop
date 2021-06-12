#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

pid_t cpid;

void signalHandler(int signum) {
	printf("\n Signal %d (%s) sent to child PID %d \n", signum, strsignal(signum), cpid);
	kill(cpid, signum);
	exit(0);
}

auto main(int argc, char *argv[]) -> int {

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  
  if (cpid == 0) {
    execvp(argv[1], argv + 1);
    perror("execve");
    exit(EXIT_FAILURE);
  }
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, signalHandler);
  signal(SIGQUIT, signalHandler);
  signal(SIGHUP, signalHandler);
   
  int status = 0;
  waitpid(cpid, &status, 0);
  if (WIFEXITED(status)) {
    printf("\n Child PID %d, exited with status %d\n", cpid, WEXITSTATUS(status));
  }
  if (WIFSIGNALED(status)) {
    printf("\n Child PID %d, killed by signal %d (%s)\n", cpid, WTERMSIG(status), strsignal(WTERMSIG(status)));
  }

  return 0;
}
