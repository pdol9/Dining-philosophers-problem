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

#include "../phil.h"

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	//sleep(1);
	int index = *(int *)arg;
	printf("%d ", primes[index]);
	//free(arg);
}
//https://www.youtube.com/watch?v=oq29KUy29iQ
// https://www.youtube.com/watch?v=HDohXvS6UIk

int	main(int ac, char *av[])
{
	pthread_t th[10];
	
	for (int i = 0; i < 10; i++)
	{
	//	int *a = malloc(sizeof(int)); test case working w/t malloc
	//	*a = i;
		if (pthread_create(&th[i], NULL, &routine, &i) != 0)
			perror("failed to create thread");
		
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("failed to join thread");
		
	}

	return (0);
}

