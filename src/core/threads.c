/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:19:59 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/12 10:10:47 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				ft_philosopher_routine, &philos[i]) != 0)
			ft_error_handler();
	}
	if (pthread_create(monitor, NULL,
			ft_monitor_routine, philos) != 0)
		ft_error_handler();
}

void	ft_join_threads(t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			ft_erro_handler();
	}
	if (pthread_join(monitor, NULL) != 0)
		ft_error_handler();
}
