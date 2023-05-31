/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 18:04:09 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_BONUS_H
# define PHIL_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <signal.h>

# define RED 	"\e[31m"
# define CLEAR	"\e[0m"

# define SEM_LOCK			"/lock"
# define SEM_STATUS			"/status"
# define SEM_FORKS			"/forks"
# define SEM_TERMINATION	"/termination"
# define SEM_ALL_FED		"/all_fed"

typedef struct s_phil
{
	int				id;
	int				meals;
	int				dead;
	pid_t			pid;
	time_t			last_meal;
	pthread_t		attendant;
	struct s_data	*data;		
}	t_phil;

typedef struct s_data
{
	sem_t			*lock;
	sem_t			*status;
	sem_t			*forks;
	sem_t			*all_fed;
	sem_t			*termination;
	int				tmp;
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	t_phil			*philosopher;
}	t_data;

typedef void	(*(*t_fptr)())();

/* validate args */
int		args_validation(int ac, char *av[]);
int		check_digit(char *str);
int		ft_atoi(const char *string);

/* init */
int		init_args(int ac, char *av[], t_data *ptr);
int		init_data(t_data *ptr);
int		init_sem(t_data *ptr);
int		initialization(int ac, char *av[], t_data *ptr);

/* main */
void	single_routine(t_phil *ph);
void	routine(t_phil *ph);
int		simulation_start(t_data *ptr);

/* routine */
void	eating(t_phil *ph);
void	sleeping(t_phil *ph);
void	thinking(t_phil *ph);

/* utils */
t_fptr	f(int n);
time_t	get_time(void);
void	display_status(t_phil *ph, char *str);
int		stop_simulation(t_phil *ph);

/* exit */
void	*controlling_status(void *arg);
void	clear_sem(t_data *data);
void	clear_terminate(t_data *ptr);

#endif
