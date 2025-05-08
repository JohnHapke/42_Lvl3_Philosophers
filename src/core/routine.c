/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/08 10:51:12 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos; // Why without malloc in this case?

	philos = (t_philo *)args;
	while (!philos->data->simulation_end)
	{
		ft_think(philos);
		// ft_print_status(philo, "has taken a fork");
		if (philos->id % 2 == 0)
		{
			pthread_mutex_lock(&philos->left_fork->mutex);
			pthread_mutex_lock(&philos->right_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&philos->right_fork->mutex);
			pthread_mutex_lock(&philos->left_fork->mutex);
		}
		ft_eat(philos);
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		ft_sleep(philos);
	}
}
