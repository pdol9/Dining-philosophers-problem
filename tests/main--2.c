/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/07/22 14:31:49 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits.h> 
# include <stdio.h> 
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
//#include "../include/philo.h"

// next -->
// https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM
//https://www.youtube.com/watch?v=ln3el6PR__Q

// https://www.youtube.com/watch?v=xoXzp4B8aQk

#define MAX 12

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

typedef struct s_data
{
	pthread_t		*th;
	pthread_mutex_t *fork;
	pthread_mutex_t mutex;
	long long start_time;
	int mails;
}	t_data;


void *routine(void *ptr)
{
	t_data *data = (t_data *)ptr;

	while (1){

		pthread_mutex_lock(&data->mutex);
		if (data->mails < 100000){
			if (data->mails % 10000)
				printf("mail arrives:  %lld\n", get_time() - data->start_time);
			data->mails++;
		}
		else{
			pthread_mutex_unlock(&data->mutex);
			return NULL;
		}
		pthread_mutex_unlock(&data->mutex);	
	}
	return NULL;
}

int	main(int ac, char *av[])
{
	t_data	*data = malloc(sizeof(*data));
	data->th = malloc(sizeof(*(data->th)) * MAX);
	data->fork = malloc(sizeof(*(data->fork)) * MAX);
	
	data->mails = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->mutex, NULL);

	int i = 0;

	while (i < MAX){
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}

	i = 0;
	while (i < MAX){
		if (pthread_create(&data->th[i], NULL, &routine, data) != 0){
			perror("failed to create thread");
			return 1;
		}
		printf("thread %d has started\n",i);
		i++;
	}
	
	printf("\n  ----- middle -----\n");
	
	i = 0;
	while (i < MAX){
		if (pthread_join(data->th[i], NULL) != 0)
			return 2;
		printf("thread %d has finished exec\n",i);
		i++;
	}

	i = 0;
	while (i < MAX){
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);


	printf("number of mails: %d\n", data->mails);
	
	free(data->th);
	free(data->fork);
	free(data);
	printf("\n  ----- OK -----\n");
	return (0);
}
