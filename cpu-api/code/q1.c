#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int x = 6;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        x = 5;
        fprintf(stdout, "child x: %d\n", x);
    } else {
        wait(NULL);
        x = 7;
        fprintf(stdout, "parent x: %d\n", x);
    }
    return 0;
}