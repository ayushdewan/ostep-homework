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
    wait(NULL);
    printf("hello\n");
  } else {
    // waitpid(rc, NULL, 0);
    printf("goodbye\n");
    // q6: see man page for waitpid, it's a superset of wait (i.e. wait(ptr) <==> waitpid(-1, ptr, 0)), waitpid let's you wait for processes in more fine-grained ways like WNOHANG
  }
  return 0;
}
