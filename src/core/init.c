/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:31:18 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/02 11:06:04 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_project(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->num_of_philo = ft_atoi(argv[1]);
		if (data->num_of_philo < 1 || data->num_of_philo > MY_INT_MAX)
			ft_error();
		data->time_to_die = ft_atoi(argv[2]);
		if (data->time_to_die < 0)
			ft_error();
		data->time_to_eat = ft_atoi(argv[3]);
		if (data->time_to_eat < 0)
			ft_error();
		data->time_to_sleep = ft_atoi(argv[4]);
		if (data->time_to_sleep < 0)
			ft_error();
		if (argc == 6)
		{
			data->meals_required = ft_atoi(argv[5]);
			if (data->meals_required < 0)
				ft_error();
		}
		ft_init_mutex(data);
	}
}

void	ft_init_mutex(t_data *data)
{
	t_fork	*forks;
	int		i;

	forks = malloc(data->num_of_philo * sizeof(t_fork));
	if (!forks)
		ft_error();
	i = -1;
	while (++i < data->num_of_philo)
	{
		forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&(forks[i].mutex), NULL) == -1)
			ft_error();
	}
	ft_init_philos(data, forks);
}

void	ft_init_philos(t_data *data, t_fork *forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(data->num_of_philo * sizeof(t_philo));
	if (!philos)
		ft_error();
	i = -1;
	while (++i < data->num_of_philo)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_of_philo];
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].data = data;
	}
}
