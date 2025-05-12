/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/12 12:49:19 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *philos, t_routine_code code)
{
	pthread_mutex_lock(&philos->data->print_mutex);
	if (!philos->data->simulation_end)
	{
		if (code == R_SLEEP)
			printf("%ld %d is sleeping\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_THINK)
			printf("%ld %d is thinking\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_EAT)
			printf("%ld %d is eating\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_FORK)
			printf("%ld %d has taken a fork\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_DEAD)
			printf("%ld %d died\n", ft_elapsed_time(philos->data), philos->id);
		else
			ft_error_handler();
	}
	pthread_mutex_unlock(&philos->data->print_mutex);
}

void	ft_think(t_philo *philos)
{
	ft_print_status(philos, R_THINK);
}

void	ft_sleep(t_philo *philos)
{
	ft_print_status(philos, R_SLEEP);
	usleep(philos->data->time_to_sleep * 1000);
}

void	ft_eat(t_philo *philos)
{
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_EAT);
	philos->last_meal = ft_get_current_time();
	usleep(philos->data->time_to_eat * 1000);
	philos->meals += 1;
}

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (philos->data->simulation_end == 0)
	{
		ft_think(&philos);
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
		ft_eat(&philos);
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		ft_sleep(&philos);
	}
}
