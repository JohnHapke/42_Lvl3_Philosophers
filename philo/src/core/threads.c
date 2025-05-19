/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:19:59 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/19 11:00:32 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_simulation_end_control(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->mutex_sim_end);
	philos->data->simulation_end = 1;
	pthread_mutex_unlock(&philos->data->mutex_sim_end);
}

int	ft_create_threads(t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				ft_philosopher_routine, &philos[i]) != 0)
		{
			ft_simulation_end_control(philos);
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			ft_error_handler(philos->data, philos, philos->left_fork, E_THREAD);
			return (1);
		}
	}
	if (pthread_create(monitor, NULL,
			ft_monitor_routine, philos) != 0)
	{
		ft_simulation_end_control(philos);
		if (ft_join_threads(philos, monitor) == 1)
			return (1);
		ft_error_handler(philos->data, philos, philos->left_fork, E_THREAD);
		return (1);
	}
	return (0);
}

int	ft_join_threads(t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			ft_error_handler(philos->data, philos, philos->left_fork, E_THREAD);
			return (1);
		}
	}
	if (pthread_join(*monitor, NULL) != 0)
	{
		ft_error_handler(philos->data, philos, philos->left_fork, E_THREAD);
		return (1);
	}
	return (0);
}
