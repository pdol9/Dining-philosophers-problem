/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 17:50:08 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	initialization(int ac, char *av[], t_data *ptr)
{
	if (init_args(ac, av, ptr) == 1)
		return (1);
	if (init_data(ptr) == 1)
	{
		free(ptr->philosopher);
		return (1);
	}
	if (init_mutex(ptr) == 1)
	{
		free(ptr->philosopher);
		free(ptr->forks);
		return (1);
	}
	return (0);
}

int	init_args(int ac, char *av[], t_data *ptr)
{
	ptr->num_philos = ft_atoi(av[1]);
	ptr->time_to_die = ft_atoi(av[2]);
	ptr->time_to_eat = ft_atoi(av[3]);
	ptr->time_to_sleep = ft_atoi(av[4]);
	ptr->start_time = get_time();
	ptr->dead = 0;
	ptr->tmp = -1;
	if (ptr->num_philos == 0)
	{
		printf(" %s>> invalid number of philosophers%s\n", RED, CLEAR);
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) > 0)
		ptr->tmp = ft_atoi(av[5]);
	else if (ac == 6 && ft_atoi(av[5]) < 1)
	{
		printf(" %s>> invalid number of meals%s\n", RED, CLEAR);
		return (1);
	}
	return (0);
}

int	init_data(t_data *ptr)
{
	int	i;

	ptr->philosopher = malloc(sizeof(*(ptr->philosopher)) * ptr->num_philos);
	if (ptr->philosopher == NULL)
		return (1);
	i = 0;
	while (i < ptr->num_philos)
	{
		ptr->philosopher[i].id = i;
		ptr->philosopher[i].last_meal = ptr->start_time;
		ptr->philosopher[i].data = ptr;
		ptr->philosopher[i].left = i;
		ptr->philosopher[i].meals = ptr->tmp;
		if (i != ptr->num_philos - 1)
			ptr->philosopher[i].right = i + 1;
		i++;
	}
	ptr->philosopher[ptr->num_philos - 1].right = 0;
	return (0);
}

int	init_mutex(t_data *ptr)
{
	int	i;

	i = 0;
	ptr->forks = malloc(sizeof(*ptr->forks) * ptr->num_philos);
	if (ptr->forks == NULL)
		return (1);
	while (i < ptr->num_philos)
	{
		if (pthread_mutex_init(&ptr->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&ptr->lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&ptr->status, NULL) != 0)
		return (1);
	return (0);
}
