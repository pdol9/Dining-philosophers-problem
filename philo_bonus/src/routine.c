/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/12 20:22:10 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

void	eating(t_phil *ph)
{
	if (stop_simulation(ph) == 1)
		return ;
	sem_wait(ph->data->forks);
	display_status(ph, "has taken a fork");
	sem_wait(ph->data->forks);
	display_status(ph, "has taken a fork");
	display_status(ph, "is eating");
	sem_wait(ph->data->status);
	ph->last_meal = get_time();
	if (ph->meals > 0)
		ph->meals--;
	if (ph->meals == 0)
		sem_post(ph->data->all_fed);
	sem_post(ph->data->status);
	usleep(ph->data->time_to_eat * 1000);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
}

void	sleeping(t_phil *ph)
{
	display_status(ph, "is sleeping");
	if (stop_simulation(ph) == 1)
		return ;
	usleep(ph->data->time_to_sleep * 1000);
}

void	thinking(t_phil *ph)
{
	display_status(ph, "is thinking");
}
