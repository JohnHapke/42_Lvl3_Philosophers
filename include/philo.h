/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:13:21 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/08 09:59:33 by jhapke           ###   ########.fr       */
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


#endif