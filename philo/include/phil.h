/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 17:45:33 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RED 	"\e[31m"
# define CLEAR	"\e[0m"

typedef struct s_phil
{
	struct s_data	*data;
	pthread_t		thread;
	time_t			last_meal;
	int				right;
	int				left;
	int				id;
	int				meals;
}	t_phil;

typedef struct s_data
{
	int				tmp;
	int				dead;
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	status;
	pthread_mutex_t	*forks;
	pthread_t		attendant;
	t_phil			*philosopher;
}	t_data;

typedef void	(*(*t_fptr)(void *));

/* args validatation */
int		args_validation(int ac, char *av[]);
int		check_digit(char *str);
int		ft_atoi(const char *string);

/* init */
int		init_args(int ac, char *av[], t_data *ptr);
int		init_data(t_data *ptr);
int		init_mutex(t_data *ptr);
int		initialization(int ac, char *av[], t_data *ptr);

/* main */
void	*single_routine(void *arg);
void	*routine(void *data);
int		simulation_start(t_data *ptr);

/* routine */
void	eating(t_data *d, t_phil *ph);
void	sleeping(t_data *d, t_phil *ph);
void	thinking(t_data *d, t_phil *ph);

/* utils */
t_fptr	f(int n);
time_t	get_time(void);
int		display_status(t_data *d, t_phil *ph, char *str);
int		verify_meals(t_data *data);

/* exit */
int		monitoring(t_data *data);
int		stop_simulation(t_data *data, t_phil *ph);
int		clear_data(t_data *ptr);

#endif
