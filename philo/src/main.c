/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 17:27:21 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	simulation_start(t_data *ptr)
{
	int	id;

	id = 0;
	while (id < ptr->num_philos)
	{
		if (pthread_create(&ptr->philosopher[id].thread, NULL, \
			f(ptr->num_philos), &(ptr->philosopher[id])) != 0)
			return (1);
		id++;
	}
	if (monitoring(ptr) == 1)
		return (1);
	return (0);
}

void	*single_routine(void *arg)
{
	t_data	*data;
	t_phil	*ph;

	ph = (t_phil *)arg;
	data = ph->data;
	display_status(data, ph, "has taken a fork");
	pthread_mutex_lock(&data->forks[ph->left]);
	usleep(data->time_to_die * 1000);
	pthread_mutex_unlock(&data->forks[ph->left]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_data	*data;
	t_phil	*ph;

	ph = (t_phil *)arg;
	data = ph->data;
	if (ph->id % 2)
		usleep(data->time_to_eat * 1000);
	while (1)
	{
		eating(data, ph);
		sleeping(data, ph);
		thinking(data, ph);
		if (stop_simulation(data, ph) == 1)
			break ;
	}
	return (NULL);
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
	if (clear_data(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
