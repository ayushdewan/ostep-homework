// https://claude.ai/chat/9d45fb27-3099-4b6b-9b95-19a5d471b06e
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

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("EXECLP:\n");
        execlp("ls", "ls", "-l", NULL);
    }
    waitpid(rc, NULL, 0);

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("EXECV:\n");
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);
    }
    waitpid(rc, NULL, 0);

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("EXECVP:\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
    }
    waitpid(rc, NULL, 0);

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("EXECVE:\n");
        char *args[] = {"ls", "-l", NULL};
        char *envp[] = {
            "CLICOLOR=1",
            "LSCOLORS=g",
            NULL,
        };
        execve("/bin/ls", args, envp);
    }
    waitpid(rc, NULL, 0);

    return 0;
}
