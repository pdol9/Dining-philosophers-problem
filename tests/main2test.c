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

t_phil	*init_data()
{
	t_phil	*ret;

	printf("  %p\n", ret);

	ret = malloc(sizeof(*ret));
	printf("  %p after\n", ret);
	printf("        sizeof struc   %ld\n", sizeof(*ret));
	printf("     think str: addr:  %p\n", &(ret->thinking_time));
	printf("   num of phil: addr:  %p\n", &(ret->maxtime_eating));
	printf("         group: addr:  %p\n", (void *)(ret->philo));
	printf("           next addr:  %p\n", (ret)+1);
	printf(" sizeof philo->group:  %ld\n", sizeof(ret->philo));
	printf("       group+1  next:  %p\n", (void *)(ret->philo)+1);
	printf("      sizeof group+1:  %ld\n", sizeof((ret->philo)+1));
	printf("         next+2 addr:  %p\n", (ret+2));
	ret->num = 5;
	ret->dying_time = 400;
	ret->eating_time = 200;
	ret->sleeping_time = 200;
	ret->thinking_time = 200;
	ret->maxtime_eating = 0;

	return (ret);
}

void *routine(void *data)
{
	// lock the variable so no other thread has access to it
	pthread_t tid = pthread_self();
	
	t_forks	*d;
	d = (t_forks *)data;


	pthread_mutex_lock(&d->fork[0]);
	//pthread_mutex_lock(&d->fork[1]);
	printf("mutex locked by - id [%ld]  %p\n",tid,&tid);
	pthread_mutex_unlock(&d->fork[0]);
	//pthread_mutex_unlock(&d->fork[1]);
	
	return NULL;
}

void	ft_threading(t_phil *th, t_forks *mutex)
{
	int	i;

	i = 0;
	while (i < th->num){
		if (pthread_create(&th->philo[i], NULL, &routine, mutex) != 0){
			perror("failed to create thread");
			return ;
		}
		//printf(" |%d| - [%ld] has started\n",i,th->group[i]);
		i++;
	}
}

void	ft_regrouping(t_phil *th)
{
	int	i;

	i = 0;
	while (i < th->num){
		if (pthread_join(th->thread[i], NULL) != 0)
			return ;
		//printf("thread |%d| - [%ld] has finished exec\n",i,th->group[i]);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_phil	*th;
	pthread_mutex_t mutex;

	th = init_data();
	pthread_mutex_init(&mutex, NULL);
	
	ft_threading(th, &mutex);
	//printf("\n  let's wrap up!\n");
	ft_regrouping(th);
	

	pthread_mutex_destroy(&mutex);
	free(th);
	printf("END !!\n");
	return (0);
}
