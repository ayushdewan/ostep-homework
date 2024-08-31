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
    printf("EXECL:\n");
    execl("/bin/ls", "ls", "-l", NULL);
  }
  waitpid(rc, NULL, 0);

  rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("EXECLE:\n");
    char *envp[] = {
      "CLICOLOR=1",
      "LSCOLORS=b",
      NULL,
    };
    execle("/bin/ls", "ls", "-l", NULL, envp);
  }
  waitpid(rc, NULL, 0);

  // now ask chat gpt to fill in the remaining 4 versions
  // the important parts are (in no order of importance):
  // change env vars, 

  return 0;
}
