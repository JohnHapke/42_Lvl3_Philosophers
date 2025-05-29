/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 08:52:44 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/29 11:41:02 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep_think(t_philo *philos)
{
	ft_print_status(philos, R_SLEEP);
	ft_exact_time(philos->data->time_to_sleep);
	ft_print_status(philos, R_THINK);
	return (ft_routine_control(philos));
}

int	ft_eat(t_philo *philos)
{
	if (ft_routine_control(philos) == 1)
		return (1);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_EAT);
	pthread_mutex_lock(&philos->mutex_meal_lock);
	philos->last_meal = ft_get_current_time();
	philos->meals += 1;
	pthread_mutex_unlock(&philos->mutex_meal_lock);
	ft_exact_time(philos->data->time_to_eat);
	return (ft_routine_control(philos));
}
