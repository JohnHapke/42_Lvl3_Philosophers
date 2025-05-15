/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:52:44 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/15 11:48:01 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_think(t_philo *philos)
{
	ft_print_status(philos, R_THINK);
	return (ft_routine_control(philos));
}

int	ft_sleep(t_philo *philos)
{
	ft_print_status(philos, R_SLEEP);
	usleep(philos->data->time_to_sleep * 1000);
	return (ft_routine_control(philos));
}

int	ft_eat(t_philo *philos)
{
	long long 	remaining_time;

	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		return (1);
	}
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_EAT);
	pthread_mutex_lock(&philos->mutex_last_meal);
	philos->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&philos->mutex_last_meal);
	remaining_time = philos->data->time_to_eat * 1000;
	while (remaining_time > 0)
	{
		if (ft_routine_control(philos) == 1)
		{
			pthread_mutex_unlock(&philos->left_fork->mutex);
			pthread_mutex_unlock(&philos->right_fork->mutex);
			return (1);
		}
		usleep(1000);
		remaining_time -= 1000;
	}
	pthread_mutex_lock(&philos->mutex_meals);
	philos->meals += 1;
	pthread_mutex_unlock(&philos->mutex_meals);
	return (ft_routine_control(philos));
}
