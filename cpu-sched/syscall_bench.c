#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <mach/mach_time.h>
#define N_SAMPLES 50

long get_time(struct timeval *tvp) {
  gettimeofday(tvp, NULL);
  long timestamp = 1000000 * tvp->tv_sec + tvp->tv_usec;
  return timestamp;
}

// only works on a dumbass m* apple processor
uint64_t get_time2(/*struct timeval *tvp*/) {
  return mach_absolute_time();
}

int main() {
  // PHASE 1
  printf("Phase 1, part 1: Testing accuracy/precision of `gettimeofday`:\n");
  struct timeval tv;
  for (int i = 0; i < 5; i++) {
    printf("%ld\n", get_time(&tv)); 
  }
  printf("seems like `gettimeofday` is pretty imprecise for testing functions that run in a matter of microseconds, subsequent system calls differ by more than ~1-2 microsecond. larger differences may be indicative of an kernel context switch.\n");

  printf("Phase 1, part 2: Testing accuracy/precision of `mach_absolute`:\n");
  for (int i = 0; i < 5; i++) {
    printf("%ld\n", (long) get_time2()); 
  }


  // PHASE 2
  printf("\n");
  printf("Phase 2: Measure cost of syscall\n");
  long sum_durations = 0;
  for (int i = 0; i < N_SAMPLES; i++) {
    uint64_t start_ts = get_time2();
    read(0, NULL, 0);
    sum_durations += get_time2() - start_ts;
  }
  double avg_duration = (double) sum_durations / N_SAMPLES;
  printf("average system call duration: %g ns\n", avg_duration);


  return 0;
}
