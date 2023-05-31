/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 23:23:18 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

void	display_status(t_phil *ph, char *str)
{
	if (stop_simulation(ph) == 1)
		return ;
	sem_wait(ph->data->lock);
	printf("%ld %d %s\n", get_time() - ph->data->start_time, ph->id + 1, str);
	sem_post(ph->data->lock);
}

int	stop_simulation(t_phil *ph)
{
	sem_wait(ph->data->status);
	if (ph->dead == 1)
	{
		sem_post(ph->data->status);
		return (1);
	}
	sem_post(ph->data->status);
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
