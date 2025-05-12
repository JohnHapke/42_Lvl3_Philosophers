/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:13:05 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/12 10:09:31 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_init_project(argc, argv, data);
	forks = ft_init_mutex(data);
	if (!forks)
		ft_error_handler();
	philos = ft_init_philos(data, forks);
	if (!forks)
		ft_error_handler();
	ft_create_threads(philos, &monitor);
	ft_join_threads(philos, &monitor);
	ft_cleanup();
}
