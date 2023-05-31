/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 18:07:47 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

int	initialization(int ac, char *av[], t_data *ptr)
{
	if (init_args(ac, av, ptr) == 1)
		return (1);
	if (init_data(ptr) == 1)
	{
		free(ptr->philosopher);
		return (1);
	}
	if (init_sem(ptr) == 1)
	{
		free(ptr->philosopher);
		clear_sem(ptr);
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
		ptr->philosopher[i].dead = 0;
		ptr->philosopher[i].meals = ptr->tmp;
		ptr->philosopher[i].last_meal = ptr->start_time;
		ptr->philosopher[i].data = ptr;
		i++;
	}
	return (0);
}

int	init_sem(t_data *ptr)
{
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_STATUS);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_TERMINATION);
	sem_unlink(SEM_ALL_FED);
	ptr->forks = sem_open(SEM_FORKS, O_CREAT, S_IRUSR | S_IWUSR,
			ptr->num_philos);
	ptr->lock = sem_open(SEM_LOCK, O_CREAT, S_IRUSR | S_IWUSR, 1);
	ptr->status = sem_open(SEM_STATUS, O_CREAT, S_IRUSR | S_IWUSR, 1);
	ptr->termination = sem_open(SEM_TERMINATION, O_CREAT, S_IRUSR | S_IWUSR, 0);
	ptr->all_fed = sem_open(SEM_ALL_FED, O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (ptr->lock == SEM_FAILED || ptr->status == SEM_FAILED \
		|| ptr->forks == SEM_FAILED || ptr->all_fed == SEM_FAILED \
		|| ptr->termination == SEM_FAILED)
	{
		printf("initialization of semaphores failed\n");
		return (1);
	}
	return (0);
}
