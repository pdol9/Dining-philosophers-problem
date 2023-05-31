/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/07/13 21:05:26 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int mails = 0;
pthread_mutex_t mutex;

void *routine(void *data)
{
	// https://www.youtube.com/watch?v=FY9livorrJI
	// race condition --> 1000000
	// gcc -S main1.c --> compile into assembly
	for (int i = 0; i < 1000000; i++){
		// lock the variable so no other thread has access to it
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int ac, char *av[])
{
	pthread_t t1, t2, t3, t4;
	//init mutex
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_join(t1, NULL) != 0)
		return 2;
	if (pthread_join(t2, NULL) != 0)
		return 2;
	if (pthread_join(t3, NULL) != 0)
		return 2;
	if (pthread_join(t4, NULL) != 0)
		return 2;

	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
	return (0);
	// instead of 2mio mails, there's 1/4 missing (data corruption)
	// using mutex there's no data corruption: 2mio out of 2mio
}
