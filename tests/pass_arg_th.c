#include "../include/philo.h"

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int index = *(int *)arg;
	printf(" prime = %d\n", primes[index]);
	free(arg);
	return NULL;
}

int main(int ac, char *av[])
{
	pthread_t th[10];

	int i = 0;
	while (i < 10){
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0){
			perror("failed to create thread");
			return 1;
		}
		i++;
	}
	printf("\n  let's wrap up!\n");
	i = 0;
	while (i < 10){
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("thread %d has finished exec\n",i);
		i++;
	}
	return 0;
}