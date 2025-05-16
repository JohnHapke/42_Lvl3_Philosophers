/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:13:21 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/16 12:01:19 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_error_code
{
	E_ARG,
	E_INIT,
	E_MEM,
	E_THREAD,
}	t_error_code;

typedef enum e_routine_code
{
	R_THINK,
	R_EAT,
	R_SLEEP,
	R_DEAD,
	R_FORK,
	R_ALL,
}	t_routine_code;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

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
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mutex_meals;
	int				meals;
	pthread_mutex_t	mutex_last_meal;
	long long		last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
}	t_philo;

// utils
int			ft_atoi(char *str);

// init
int			ft_init_project(int argc, char **argv, t_data *data);
void		ft_init_time(t_data *data);
t_fork		*ft_init_mutex(t_data *data);
t_philo		*ft_init_philos(t_data *data, t_fork *forks);

// time
long long	ft_get_current_time(void);
long long	ft_elapsed_time(t_data *data);

// single philo
int			ft_handle_single_philo(t_data *data);

// threads
int			ft_create_threads(t_philo *philos, pthread_t *monitor);
int			ft_join_threads(t_philo *philos, pthread_t *monitor);
void		ft_simulation_end_control(t_philo *philos);

// activity
int			ft_eat(t_philo *philos);
int			ft_sleep(t_philo *philos);
int			ft_think(t_philo *philos);

// routine
void		*ft_philosopher_routine(void *args);
void		ft_print_status(t_philo *philos,
				t_routine_code code);
int			ft_routine_control(t_philo *philos);
int			ft_routine_mutex(t_philo *philos);
int			ft_routine_odd_philos(t_philo *philos);
int			ft_routine_even_philos(t_philo *philos);

// monitor
void		*ft_monitor_routine(void *args);
int			ft_monitor_time(t_philo *philos);
int			ft_monitor_meals(t_philo *philos);

// error & cleanup
void		ft_error_handler(t_data *data, t_philo *philos,
				t_fork *forks, t_error_code code);
void		ft_cleanup_mutex(t_data *data, t_philo *philos, t_fork *forks);
void		ft_cleanup_memory(t_data *data, t_philo *philos, t_fork *forks);

// project handler
int			ft_project_handler(t_data *data);

#endif