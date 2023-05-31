#include "../include/philo.h"

#define THR_NUM 10

typedef struct Task
{
	int a, b;
}	Task;

Task taskQueue[256];
int	taskCount = 0;

pthread_mutex_t mutexQueue;

void	*executeTask(Task *task)
{
	int result = task->a + task->b;
	printf("the sum of %d and %d is %d\n", task->a, task->b, result);
}

void	submitTask(Task task)
{
	pthread_mutex_lock(&mutexQueue);
	taskQueue[taskCount] = task;
	taskCount++;
	pthread_mutex_unlock(&mutexQueue);
}

void	*routine(void *arg)
{
	while (1)
	{
		Task task;
		int found = 0;

		pthread_mutex_lock(&mutexQueue);
		if (taskCount > 0)
		{
			found = 1;
			task = taskQueue[0];
			for (int i = 0; i < taskCount; i++)
				taskQueue[i] = taskQueue[i + 1];
			taskCount--;
		}
		pthread_mutex_unlock(&mutexQueue);
		if (found == 1)
			executeTask(&task);

	}
	return NULL;
}

int main(int ac, char *av[])
{
	pthread_t	th[THR_NUM];
	pthread_mutex_init(&mutexQueue, NULL);

	int i = 0;
	while (i < THR_NUM){
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0){
			perror("failed to create thread");
			return 1;
		}
		//printf("thread %d has started\n",i);
		i++;
	}

	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		Task t = {
			.a = rand() % 100,
			.b = rand() % 100,
		};
		submitTask(t);
	}

	i = 0;
	while (i < THR_NUM){
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("thread %d has finished exec\n",i);
		i++;
	}

	pthread_mutex_destroy(&mutexQueue);
	return 0;
}