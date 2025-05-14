/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:31:18 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/14 09:19:56 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_project(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->num_of_philo = ft_atoi(argv[1]);
		if (data->num_of_philo < 1 || data->num_of_philo > MY_INT_MAX)
			ft_error_handler(data, NULL, NULL, E_INIT);
		data->time_to_die = ft_atoi(argv[2]);
		if (data->time_to_die < 0)
			ft_error_handler(data, NULL, NULL, E_INIT);
		data->time_to_eat = ft_atoi(argv[3]);
		if (data->time_to_eat < 0)
			ft_error_handler(data, NULL, NULL, E_INIT);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (data->time_to_sleep < 0)
			ft_error_handler(data, NULL, NULL, E_INIT);
		data->meals_required = -1;
		data->simulation_end = 0;
		if (argc == 6)
		{
			data->meals_required = ft_atoi(argv[5]);
			if (data->meals_required < 0)
				ft_error_handler(data, NULL, NULL, E_INIT);
		}
		ft_init_time(data);
	}
}

void	ft_init_time(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	data->simulation_time = current_time.tv_sec
		* 1000 + current_time.tv_usec / 1000;
}

t_fork	*ft_init_mutex(t_data *data)
{
	t_fork	*forks;
	int		i;

	forks = malloc(data->num_of_philo * sizeof(t_fork));
	if (!forks)
		ft_error_handler(data, NULL, forks, E_MEM);
	i = -1;
	while (++i < data->num_of_philo)
	{
		forks[i].fork_id = i + 1;
		pthread_mutex_init(&(forks[i].mutex), NULL);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	return (forks);
}

t_philo	*ft_init_philos(t_data *data, t_fork *forks)
{
	int		i;
	t_philo	*philos;

	philos = malloc(data->num_of_philo * sizeof(t_philo));
	if (!philos)
		ft_error_handler(data, philos, forks, E_MEM);
	i = -1;
	while (++i < data->num_of_philo)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_of_philo];
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].data = data;
		philos[i].last_meal = data->simulation_time;
		pthread_mutex_init(&philos[i].mutex_meals, NULL);
		pthread_mutex_init(&philos[i].mutex_last_meal, NULL);
	}
	return (philos);
}
