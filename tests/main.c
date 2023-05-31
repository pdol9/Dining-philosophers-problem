/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/07/20 21:55:21 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

void *routine()
{
	printf("start of a new thread\n");
	sleep(3);
	printf("ending thread\n");
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_join(t1, NULL) != 0)
		return 1;
	if (pthread_join(t2, NULL) != 0)
		return 1;

	return (0);
}

