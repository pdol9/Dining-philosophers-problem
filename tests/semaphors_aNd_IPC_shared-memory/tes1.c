

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/wait.h>


void	child(void)
{
	sem_t	*sem_mutex;
	int	i;

	printf("\e[36mChild: Hi! I'm the child.\e[0m\n");
	// Opens the same semaphore as the main process:
	sem_mutex = sem_open("/test_sem", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (sem_mutex == SEM_FAILED)
		exit(EXIT_FAILURE);
	i = 5;
	while (i > 0)
	{
		// Increments the semaphore's value by 1:
		sem_post(sem_mutex);
		sleep(5);
		i--;
	}
    // Close the semaphore
	sem_close(sem_mutex);
	exit(EXIT_SUCCESS);
}

void	parent(pid_t pid, sem_t *sem_mutex)
{
	int	status;
	int	count;

	count = 0;
	// Loop 5 times to avoid a deadlock, since the child
	// is going to decrement the semaphore 5 times. Otherwise
	// we will stay blocked infinitely waiting for the semaphore.
	while (count < 5)
	{
		// Wait for the child to post the semaphore in order to
		// decrement it back down to 0:
		sem_wait(sem_mutex);
		count++;
		printf("Parent: My child has unlocked the semaphore %d times.\n", count);
	}
	// Wait for the child's return:
	if (waitpid(pid, &status, 0) != 0)
	{
		if (WIFEXITED(status))
			printf("Parent: My child terminated normally.\n");
	}
	//waitpid(-1, NULL, WNOHANG);
}

int	main(void)
{
	pid_t	pid;
	sem_t	*sem_mutex; // Memory address of the semaphore

	sem_mutex = sem_open("/test_sem", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (sem_mutex == SEM_FAILED)
		return (EXIT_FAILURE);
	// Decrement the semaphore's value by 1
	sem_wait(sem_mutex);
	// Create child process
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		child();
	parent(pid, sem_mutex);
	// Close and unlink semaphore
	sem_close(sem_mutex);
	sem_unlink("/test_sem");
	return (EXIT_SUCCESS);
}

/* 

pid_t waitpid(pid_t pid, int *status, int options);

The value of pid can be:

    < -1: Wait for any child process whose process group ID 
	is equal to the absolute value of pid.
    
	-1: Wait for any child process.
   
    0: Wait for any child process whose process group ID 
	is equal to that of the calling process.
   
    > 0: Wait for the child whose process ID is equal 
	to the value of pid.

The value of options is an OR of zero or more of the following constants:

    WNOHANG: Return immediately if no child has exited.
   
    WUNTRACED: Also return if a child has stopped. 
	Status for traced children which have stopped is provided 
	even if this option is not specified.
    
	WCONTINUED: Also return if a stopped child has been resumed 
	by delivery of SIGCONT.


 */