/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 14:18:27 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

int	simulation_start(t_data *data)
{
	int	id;

	id = 0;
	while (id < data->num_philos)
	{
		data->philosopher[id].pid = fork();
		if (data->philosopher[id].pid == -1)
			return (1);
		else if (data->philosopher[id].pid == 0)
			(f(data->num_philos))(&data->philosopher[id]);
		usleep(50);
		id++;
	}
	clear_terminate(data);
	return (0);
}

void	single_routine(t_phil *ph)
{
	t_data	*data;

	data = ph->data;
	if (pthread_create(&ph->attendant, NULL, &controlling_status, ph) != 0)
		return ;
	sem_wait(data->forks);
	display_status(ph, "has taken a fork");
	usleep(data->time_to_die * 1000);
	sem_post(data->forks);
	sem_post(ph->data->termination);
}

void	routine(t_phil *ph)
{
	if (pthread_create(&ph->attendant, NULL, &controlling_status, ph) != 0)
		return ;
	if (ph->id % 2)
		usleep(ph->data->time_to_eat * 1000);
	while (1)
	{
		eating(ph);
		sem_wait(ph->data->status);
		if (ph->dead == 1 || ph->meals == 0)
		{
			sem_post(ph->data->status);
			break ;
		}
		sem_post(ph->data->status);
		sleeping(ph);
		thinking(ph);
	}
	exit(0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (args_validation(ac, av))
		return (EXIT_FAILURE);
	if (initialization(ac, av, &data))
		return (EXIT_FAILURE);
	if (simulation_start(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
