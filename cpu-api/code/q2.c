#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void write_val(const char *src, int fd, int val) {
    char buf[50];
    int n = sprintf(buf, "%s x: %d\n", src, val);
    write(fd, buf, n);
    fprintf(stdout, "%s", buf);
}

int main() {
    int x = 6;
    int fd = creat("./y.txt", O_CREAT | O_WRONLY | O_TRUNC);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        x = 4;
        for(int i = 0; i < 100; i++) write_val("child", fd, x);
    } else {
        x = 7;
        for(int i = 0; i < 100; i++) write_val("parent", fd, x);
    }
    // note: removing this causes the processes to interleave: x.txt
    // note: adding this causes parent first then child behavior
    // close(fd);
    return 0;
}
