#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <mach/mach_time.h>
#define N_SAMPLES 5

// NOTE: sched_setaffinity not available on my processor, code is untested
// TODO: test this on a unix machine with a x86-64 processor

// only works on a dumbass m* apple processor
uint64_t get_time() {
  return mach_absolute_time();
}

int main() {
  int pipe1_fd[2];
  int pipe2_fd[2];
  pipe(pipe1_fd);
  pipe(pipe2_fd);

  int child1_pid = fork();
  if (child1_pid == 0) {
    char buf = 'a';
    for (int i = 0; i < 500; i++) {
      write(pipe1_fd[1], &buf, 1);
      read(pipe2_fd[0], &buf, 1);
      uint64_t timestamp = get_time();
      printf("Process 1: %llu\n", timestamp);
    }
    exit(0);
  }

  int child2_pid = fork();
  if (child2_pid == 0) {
    char buf = 'a';
    while (1) {
      read(pipe1_fd[0], &buf, 1);
      write(pipe2_fd[1], &buf, 1);
      uint64_t timestamp = get_time();
      printf("Process 2: %llu\n", timestamp);
    }
    exit(0);
  }
  return 0;
}
