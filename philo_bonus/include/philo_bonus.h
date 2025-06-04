/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:48:50 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/04 14:58:49 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

# define MY_INT_MIN -2147483648
# define MY_INT_MAX 2147483647

typedef enum e_error_code
{
	E_ARG,
	E_INIT,
	E_MEM,
	E_SEMA,
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

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		simulation_time;
	int				simulation_end;
	sem_t			*sem_simulation_end;
	sem_t			*sem_forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	sem_t			sem_forks;
	t_data			*data;
}	t_philo;

// handler

int		ft_project_handler(t_data *data);

// init

int		ft_init_project(int argc, char **argv, t_data *data);
void	ft_init_time(t_data *data);
t_philo	*ft_init_philos(t_data *data, int id);

// utils

int		ft_atoi(char *str);

// routine

void	ft_philosopher_routine(t_philo *philos);

// activity

int		ft_eat(t_philo *philos);
int		ft_sleep_think(t_philo *philos);

#endif