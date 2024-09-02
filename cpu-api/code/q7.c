#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("what happens?\n");
    // answer: ^ does not print, exits normally
  } else {
    int status;
    int ret = waitpid(rc, &status, 0);
    if (ret == -1) {
      fprintf(stderr, "waitpid failed\n");
      exit(1);
    }
    if (WIFEXITED(status)) {
      int exit_status = WEXITSTATUS(status);
      printf("Child process exit status: %d\n", exit_status);
    }
    printf("goodbye\n");
  }
  return 0;
}
