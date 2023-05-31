/* 
Either approach will work. Pick one and go with it - though I personally prefer 
named semaphores because you don't have to deal with memory allocation and with 
setting up the shared memory segments. The interface for creating and using named 
semaphores is way more friendly, in my opinion.

With named semaphores, in your example scenario, here's what happens:

    You create and initialize the semaphore in the parent process with sem_open(3). 
	Give it a well-known name that the child processes will know; this name is 
	used to find the semaphore in the system.

    Close the semaphore in the parent, since it won't be using it. Fork and execute
    Unlink the semaphore with sem_unlink(3). This must be done exactly once; it doesn't 
	really matter where (any process that has a reference to the semaphore object can do it). 
	It is ok to unlink a semaphore if other processes still have it open: the semaphore 
	is destroyed only when all other processes have closed it, but keep in mind that the name 
	is removed immediately, so new processes won't be able to find and open the semaphore.

The child processes call sem_open(3) with the well-known name to find and obtain a reference 
to the semaphore. Once a process is done with the semaphore, you need to close it with sem_close(3).

Below is an example of what I just described. A parent process creates a named semaphore, 
and forks + executes 2 child processes, each of which finds and opens the semaphore, 
using it to synchronize between each other.

It assumes that the parent forks and executes the ./sem_chld binary. Keep in mind that a name 
for a semaphore must begin with a forward slash, followed by one or more characters that are 
not a slash (see man sem_overview). In this example, the semaphore's name is /semaphore_example.

Here's the code for the parent process:


--> check semaphores on macos: 
	lsof | grep PSXSEM


 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SEM_NAME "/semaphore_example"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define INITIAL_VALUE 1

#define CHILD_PROGRAM "./sem_chld"

int main(void) {

    /* We initialize the semaphore counter to 1 (INITIAL_VALUE) */
    sem_t *semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);

    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) error");
        exit(EXIT_FAILURE);
    }

    /* Close the semaphore as we won't be using it in the parent process */
    if (sem_close(semaphore) < 0) {
        perror("sem_close(3) failed");
        /* We ignore possible sem_unlink(3) errors here */
        sem_unlink(SEM_NAME);
        exit(EXIT_FAILURE);
    }

    pid_t pids[2];
    size_t i;

    for (i = 0; i < sizeof(pids)/sizeof(pids[0]); i++) {
        if ((pids[i] = fork()) < 0) {
            perror("fork(2) failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            if (execl(CHILD_PROGRAM, CHILD_PROGRAM, NULL) < 0) {
                perror("execl(2) failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (i = 0; i < sizeof(pids)/sizeof(pids[0]); i++)
        if (waitpid(pids[i], NULL, 0) < 0)
            perror("waitpid(2) failed");

    if (sem_unlink(SEM_NAME) < 0)
        perror("sem_unlink(3) failed");

    return 0;
}
/* 
Note that sem_unlink(3) is called after both children terminate; although 
this is not required, if it was called before there would be a race condition 
between the parent process unlinking the semaphore and both child processes 
starting up and opening the semaphore. In general, though, you can unlink 
as soon as you know that all required processes have opened the semaphore and 
no new processes will need to find it.

Here's the code for sem_chld, it's just a small toy program to show the usage of a shared semaphore:
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_NAME "/semaphore_example"
#define ITERS 10

int main(void) {
    sem_t *semaphore = sem_open(SEM_NAME, O_RDWR);
    if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < ITERS; i++) {
        if (sem_wait(semaphore) < 0) {
            perror("sem_wait(3) failed on child");
            continue;
        }

        printf("PID %ld acquired semaphore\n", (long) getpid());

        if (sem_post(semaphore) < 0) {
            perror("sem_post(3) error on child");
        }

        sleep(1);
    }

    if (sem_close(semaphore) < 0)
        perror("sem_close(3) failed");

    return 0;
}
/* 
You can eliminate the need to keep the semaphore name synchronized 
between the two source files by defining it in a common header file and 
including it in the code for each program.

Note that error handling is not ideal in this example (it's merely illustrative), 
there is a lot of room for improvement. It's just there to make sure you don't forget to do 
proper error handling when you decide to change this example to suit your needs.


The shared memory approach won't work here, as the OP is calling execvp in the children. – 


By "shared memory approach" I assumed the OP wanted to avoid calling *_open in the children 
(as by inheriting the resource, which can't be done across an exec).
 */
