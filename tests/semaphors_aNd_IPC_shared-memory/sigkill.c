
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


void    child(void)
{
    printf("Child: I'm a child. I'm in an infinite loop\n");
    while (1)
        continue;
}

void    kill_children(pid_t *pid)
{
    int	status;
    int	i;

    printf("Parent: finish all the children.\n");
    i = 0;
    while (i < 3)
    {
        kill(pid[i], SIGKILL);
        i++;
    }
    printf("Parent: all children killed \n");
    // get their exit status
    i = 0;
    while (i < 3) 
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            printf("Parent: Child [%d] terminated normally.\n", pid[i]);
        else if (WIFSIGNALED(status))
        {
            printf("Parent: Child [%d] was interrupted.\n", pid[i]);
            if (WTERMSIG(status) == SIGTERM)
                printf("\e[31mParent: Child [%d] got the %d signal, SIGTERM\e[0m\n",
                            pid[i], WTERMSIG(status));
            if (WTERMSIG(status) == SIGKILL)
                printf("\e[31mParent: Child [%d] got the %d signal, SIGKILL\e[0m\n",
                            pid[i], WTERMSIG(status));
        }
        i++;
    }
}

int    main(void)
{
    pid_t    pid[3];
    int      i;

    i = 0;
    while (i < 3)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return (EXIT_FAILURE);
        else if (pid[i] == 0)
            child();
        else if (pid[i] > 0)
            printf("Parent: Child #%d created with pid = %d\n", i, pid[i]);
        usleep(1000);
        i++;
    }
    kill_children(pid);
    return (EXIT_SUCCESS);
}


