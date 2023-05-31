
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>


#define RET 42

void	child(pid_t pid)
{
	printf("Child: child process here. my PID - %d\n", pid);
	printf("Child: Exiting with code %d\n", RET);
	exit(RET);
}


void	parent(pid_t pid)
{
	int	status;

	printf("Parent: parent here. my PID - %d\n", pid);
	printf("Parent: Waiting for my child with PID [%d].\n", pid);
	
	waitpid(pid, &status, 0); // Wait for child
	printf("Parent: My child exited with status %d\n", status);
	if (WIFEXITED(status)) // If child exited normally
	{
		printf("Parent: My child's exit code is %d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == RET)
			printf("Parent: That's the expected code\n");
		else
			printf("Parent: this was not expected ...\n");
	}
}

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		child(pid);
	parent(pid);
	return (EXIT_SUCCESS);
}

/* macros:

    WIFEXITED(status): returns true if the child terminated normally, 
	for example by calling exit or finishing through the main function
	of the program.
       
	WEXITSTATUS(status): to be used only if WIFEXITED returned true. 
	Returns the child’s exit code, meaning the number the child 
	specified to the exit function or in the main function’s return.
    
	WIFSIGNALED(status): returns true if the child was forcefully 
	terminated with a signal.
    
	WTERMSIG(status): to be used only if WIFSIGNALED returned true.
	Returns the signal number that provoked the child’s termination.

 */
