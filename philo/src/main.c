/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:13:05 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/16 10:14:22 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_project_handler(t_data *data)
{
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;

	forks = ft_init_mutex(data);
	if (!forks)
	{
		ft_error_handler(data, NULL, NULL, E_MEM);
		return (1);
	}
	philos = ft_init_philos(data, forks);
	if (!philos)
	{
		ft_error_handler(data, NULL, forks, E_MEM);
		return (1);
	}
	if (ft_create_threads(philos, &monitor) == 1)
		return (1);
	if (ft_join_threads(philos, &monitor) == 1)
		return (1);
	ft_cleanup_mutex(data, philos, forks);
	ft_cleanup_memory(data, philos, forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		ft_error_handler(NULL, NULL, NULL, E_ARG);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_error_handler(NULL, NULL, NULL, E_MEM);
		return (1);
	}
	if (ft_init_project(argc, argv, data) == 1)
		return (1);
	if (data->num_of_philo == 1)
	{
		if (ft_handle_single_philo(data) == 1)
			return (1);
	}
	else if (ft_project_handler(data) == 1)
		return (1);
	return (0);
}
