/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/10 18:59:43 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	eating(t_data *d, t_phil *ph)
{
	if (display_status(d, ph, NULL) == 1)
		return ;
	pthread_mutex_lock(&d->forks[ph->left]);
	display_status(d, ph, "has taken a fork");
	pthread_mutex_lock(&d->forks[ph->right]);
	display_status(d, ph, "has taken a fork");
	display_status(d, ph, "is eating");
	pthread_mutex_lock(&d->status);
	ph->last_meal = get_time();
	if (ph->meals > 0)
		ph->meals--;
	pthread_mutex_unlock(&d->status);
	usleep(d->time_to_eat * 1000);
	pthread_mutex_unlock(&d->forks[ph->left]);
	pthread_mutex_unlock(&d->forks[ph->right]);
}

void	sleeping(t_data *d, t_phil *ph)
{
	if (display_status(d, ph, "is sleeping") == 1)
		return ;
	usleep(d->time_to_sleep * 1000);
}

void	thinking(t_data *d, t_phil *ph)
{
	display_status(d, ph, "is thinking");
}
