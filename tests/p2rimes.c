/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/07/13 18:06:45 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
//https://www.youtube.com/watch?v=oq29KUy29iQ
// https://www.youtube.com/watch?v=HDohXvS6UIk

// https://www.youtube.com/watch?v=Adtrk3PREQI

void *routine(void *arg)
{
	int index = *(int *)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes[index + j];
	printf("local sum : %d\n",sum);
	*(int *) arg = sum;
	return arg;
}

int	main(int ac, char *av[])
{
	pthread_t th[2];
	int i;

	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("failed to create thread");
	}
	int global_sum = 0;
	for (int i = 0; i < 2; i++)
	{
		int *r;
		if (pthread_join(th[i], (void **) &r) != 0)
			perror("failed to join thread");
		global_sum += *r;
		free(r);
	}
	printf("global sum = %d\n", global_sum);
	return (0);
}

