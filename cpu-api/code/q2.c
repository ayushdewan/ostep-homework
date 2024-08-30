#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int x = 6, fd = creat("./x.txt", O_CREAT | O_WRONLY | O_TRUNC);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        x = 4;

        char buf[50];
        int n = sprintf(buf, "childx:%d\n", x);
        fprintf(stdout, "%s\n", buf);
        write(fd, buf, n);
        close(fd);
    } else {
        wait(NULL);
        x = 7;
        fprintf(stdout, "parent x: %d\n", x);
        close(fd);
    }
    return 0;
}