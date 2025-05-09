/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:13:21 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/09 10:08:15 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MY_INT_MIN -2147483648
# define MY_INT_MAX 2147483647

typedef enum e_routine_code
{
	R_THINK,
	R_EAT,
	R_SLEEP,
	R_DEAD,
	R_FORK,
}	t_routine_code;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			state;
	int			meals;
	long long	last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_fork		*reference;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		simulation_time;
	int				simulation_end;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_data;

// utils
int			ft_atoi(char *str);

// core
void		ft_init_project(int argc, char **argv, t_data *data);
void		ft_time_init(t_data *data);
void		ft_init_mutex(t_data *data);
void		ft_init_philos(t_data *data, t_fork *forks);

// time
long long	ft_get_current_time(void);
long long	ft_elapsed_time(t_data *data);

// threads
void		ft_create_threads(t_data *data);
void		*ft_monitor_routine(void *args);

// routine
void		*ft_philosopher_routine(void *args);
void		ft_eat(t_philo *philos);
void		ft_sleep(t_philo *philos);
void		ft_think(t_philo *philos);
void		ft_print_status(t_philo *philos,
				t_routine_code code);
#endif