/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/10 21:58:38 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	display_status(t_data *data, t_phil *ph, char *str)
{
	if (stop_simulation(data, ph) == 1)
		return (1);
	if (str != NULL)
	{
		pthread_mutex_lock(&data->lock);
		printf("%ld %d %s\n", get_time() - data->start_time, ph->id + 1, str);
		pthread_mutex_unlock(&data->lock);
	}
	return (0);
}

int	stop_simulation(t_data *data, t_phil *ph)
{
	pthread_mutex_lock(&data->status);
	if (ph->meals == 0 || data->dead == 1)
	{
		pthread_mutex_unlock(&data->status);
		return (1);
	}
	pthread_mutex_unlock(&data->status);
	return (0);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_fptr	f(int n)
{
	if (n == 1)
		return ((void *)single_routine);
	else
		return ((void *)routine);
}

int	verify_meals(t_data *data)
{
	int	i;

	if (data->tmp == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->status);
		if (data->philosopher[i].meals != 0)
		{
			pthread_mutex_unlock(&data->status);
			return (0);
		}
		pthread_mutex_unlock(&data->status);
		i++;
	}
	return (1);
}
