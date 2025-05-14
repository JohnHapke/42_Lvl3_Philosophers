/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/14 11:29:37 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Prüfe simulation_end nach jedem Schritt in ft_philosopher_routine.
Gib Gabel-Mutexes frei, wenn simulation_end gesetzt ist.
Ändere ft_print_status, um „died“ auch bei gesetztem simulation_end auszugeben.*/
void	ft_print_status(t_philo *philos, t_routine_code code)
{
	pthread_mutex_lock(&philos->data->print_mutex);
	if (!philos->data->simulation_end)
	{
		if (code == R_SLEEP)
			printf("%lld %d is sleeping\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_THINK)
			printf("%lld %d is thinking\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_EAT)
			printf("%lld %d is eating\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (code == R_FORK)
			printf("%lld %d has taken a fork\n",
				ft_elapsed_time(philos->data), philos->id);
		else if (!philos->data->simulation_end || code == R_DEAD)
			printf("%lld %d died\n", ft_elapsed_time(philos->data), philos->id);
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
	pthread_mutex_lock(&philos->mutex_last_meal);
	philos->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&philos->mutex_last_meal);
	usleep(philos->data->time_to_eat * 1000);
	pthread_mutex_lock(&philos->mutex_meals);
	philos->meals += 1;
	pthread_mutex_unlock(&philos->mutex_meals);
}

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (philos->data->simulation_end == 0)
	{
		ft_think(philos);
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
	return (NULL);
}
