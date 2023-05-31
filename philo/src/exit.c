/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 17:42:52 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

static
void	*controlling_status(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (verify_meals(data) == 0)
	{
		pthread_mutex_lock(&data->status);
		if (get_time() - data->philosopher[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->lock);
			printf("%ld ", get_time() - data->start_time);
			printf("%d died\n", data->philosopher[i].id + 1);
			pthread_mutex_unlock(&data->lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->status);
			break ;
		}
		i++;
		if (i == data->num_philos)
			i = 0;
		pthread_mutex_unlock(&data->status);
	}
	return (NULL);
}

int	monitoring(t_data *data)
{
	int	i;

	if (pthread_create(&data->attendant, NULL, &controlling_status, data) != 0)
	{
		printf(" >> failed to create monitoring thread");
		return (1);
	}
	usleep(50);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->status);
		if (data->philosopher[i].meals == 0 || data->dead == 1)
		{
			pthread_mutex_unlock(&data->status);
			break ;
		}
		i++;
		if (i == data->num_philos)
			i = 0;
		pthread_mutex_unlock(&data->status);
	}
	return (0);
}

static
int	join_threads(t_data *ptr)
{
	int	i;

	if (pthread_join(ptr->attendant, NULL) != 0)
		return (1);
	i = 0;
	while (i < ptr->num_philos)
	{
		if (pthread_join(ptr->philosopher[i].thread, NULL) != 0)
		{
			printf(" >> failed to join threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	clear_data(t_data *ptr)
{
	int	i;

	if (join_threads(ptr) == 1)
		return (1);
	i = 0;
	while (i < ptr->num_philos)
	{
		if (pthread_mutex_destroy(&ptr->forks[i]))
			return (1);
		i++;
	}
	pthread_mutex_destroy(&ptr->lock);
	pthread_mutex_destroy(&ptr->status);
	free(ptr->philosopher);
	free(ptr->forks);
	return (0);
}
