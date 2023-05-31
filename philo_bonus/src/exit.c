/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 18:05:01 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

void	*controlling_status(void *arg)
{
	t_phil	*ph;

	ph = (t_phil *)arg;
	pthread_detach(ph->attendant);
	while (1)
	{
		sem_wait(ph->data->status);
		if (get_time() - ph->last_meal > ph->data->time_to_die)
		{
			ph->dead = 1;
			sem_wait(ph->data->lock);
			printf("%ld ", get_time() - ph->data->start_time);
			printf("%d died\n", ph->id + 1);
			sem_post(ph->data->lock);
			sem_post(ph->data->status);
			sem_post(ph->data->termination);
			return (NULL);
		}
		sem_post(ph->data->status);
		usleep(100);
	}
	return (NULL);
}

void	clear_sem(t_data *data)
{
	sem_close(data->lock);
	sem_close(data->status);
	sem_close(data->forks);
	sem_close(data->termination);
	sem_close(data->all_fed);
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_STATUS);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_TERMINATION);
	sem_unlink(SEM_ALL_FED);
}

void	clear_terminate(t_data *data)
{
	int	i;

	i = 0;
	if (data->philosopher[i].meals != -1 && data->num_philos != 1)
	{
		while (i < data->num_philos)
		{
			sem_wait(data->all_fed);
			i++;
		}
		usleep(data->time_to_eat * 1000);
		sem_post(data->termination);
	}
	sem_wait(data->termination);
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philosopher[i].pid, SIGTERM);
		i++;
	}
	clear_sem(data);
	free(data->philosopher);
}
