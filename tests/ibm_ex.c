
/* CELEBP28 */
#define _OPEN_SYS
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

void *thread(void *arg) {
  char *ret;
  printf("thread() entered with argument '%s'\n", (char *)arg);
  if ((ret = (char*) malloc(20)) == NULL) {
    perror("malloc() error");
    exit(2);
  }
  strcpy(ret, "This is a test");
  pthread_exit(ret);
}

int
main() {
  pthread_t thid;
  void *ret;

  if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_join_d4_np(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }

  printf("thread exited with '%s'\n", (char *)ret);

  if (pthread_detach(&thid) != 0) {
    perror("pthread_detach() error");
    exit(4);
  }
}

/*
Output:

thread() entered with argument 'thread 1'
thread exited with 'This is a test'

*/