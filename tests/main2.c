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

#include "../include/philo.h"

// next -->
// https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM
//https://www.youtube.com/watch?v=ln3el6PR__Q

// https://www.youtube.com/watch?v=xoXzp4B8aQk
int mails = 0;
pthread_mutex_t mutex;

void *routine(void *data)
{
	// gcc -S main1.c --> compile into assembly
	for (int i = 0; i < 100000; i++){
		// lock the variable so no other thread has access to it
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int	main(int ac, char *av[])
{
	pthread_t	th[8];
	pthread_mutex_init(&mutex, NULL);

	int i = 0;
	while (i < 8){
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0){
			perror("failed to create thread");
			return 1;
		}
		printf("thread %d has started\n",i);
		i++;
	}
	printf("\n  wrap up\n");
	i = 0;
	while (i < 8){
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("thread %d has finished exec\n",i);
		i++;
	}

	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
	return (0);
}
