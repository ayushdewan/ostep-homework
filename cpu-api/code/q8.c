#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  if (pipe(fd) == -1) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    int x = 69;
    write(fd[1], &x, sizeof(x));
    printf("Fork 1 wrote: %d\n", x);
  }

  rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    int y;
    read(fd[0], &y, sizeof(y));
    printf("Fork 2 read: %d\n", y);
  } 
  return 0;
}
