/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/16 11:28:51 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_routine_control(t_philo *philos)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philos->data->print_mutex);
	if (philos->data->simulation_end == 1)
		flag = 1;
	pthread_mutex_unlock(&philos->data->print_mutex);
	return (flag);
}

int	ft_routine_even_philos(t_philo *philos)
{
	pthread_mutex_lock(&philos->left_fork->mutex);
	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		return (1);
	}
	pthread_mutex_lock(&philos->right_fork->mutex);
	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		return (1);
	}
	return (0);
}

int	ft_routine_odd_philos(t_philo *philos)
{
	pthread_mutex_lock(&philos->right_fork->mutex);
	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&philos->right_fork->mutex);
		return (1);
	}
	pthread_mutex_lock(&philos->left_fork->mutex);
	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		return (1);
	}
	return (0);
}

int	ft_routine_mutex(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		if (ft_routine_even_philos(philos) == 1)
			return (1);
	}
	else
	{
		if (ft_routine_odd_philos(philos) == 1)
			return (1);
	}
	return (0);
}

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (ft_routine_control(philos) == 0)
	{
		if (ft_think(philos) == 1)
			break ;
		if (ft_routine_mutex(philos) == 1)
			break ;
		if (ft_eat(philos) == 1)
		{
			pthread_mutex_unlock(&philos->left_fork->mutex);
			pthread_mutex_unlock(&philos->right_fork->mutex);
			break ;
		}
		pthread_mutex_unlock(&philos->right_fork->mutex);
		pthread_mutex_unlock(&philos->left_fork->mutex);
		if (ft_sleep(philos) == 1)
			break ;
	}
	return (NULL);
}
