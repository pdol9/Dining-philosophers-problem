#include "../include/philo.h"
#include <errno.h>

pthread_mutex_t mutex_fuel;
pthread_cond_t	cond_fuel;
int fuel = 0;

void	*fuel_filling(void *arg)
{
	for (int i = 0; i < 5; ++i)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 15;
		printf("filling fuel tanker ... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_signal(&cond_fuel);
		sleep(1);
	}
}

void	*car(void *arg)
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel < 40)
	{
		printf("not enough fuel. waiting ....\n");
		// this thread will wait (check while condition) until we send a signal 
		// from another thread (fuel_filling)
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
		/* equivalent to --> pthread_mutex_unlock(&mutex_fuel)
		wait for signal on cond_fuel
		then call pthread_mutex_lock(&mutex_fuel) again */
	}
	fuel -= 40;
	printf("filling car - got fuel. now left: %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
}

int
main(int ac, char *av[])
{
	pthread_t	th[2];
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);

	for (int i = 0; i < 2; ++i)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("failed to create a thread");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("failed to create a thread");
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("failed to join a thread");
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return 0;
}
