/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/29 11:42:58 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_routine_control(t_philo *philos)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philos->data->mutex_sim_end);
	if (philos->data->simulation_end == 1)
		flag = 1;
	pthread_mutex_unlock(&philos->data->mutex_sim_end);
	return (flag);
}

int	ft_take_forks(t_philo *philos)
{
	t_fork	*first_fork;
	t_fork	*second_fork;
	
	if (philos->left_fork->fork_id < philos->right_fork->fork_id)
	{
		first_fork = philos->left_fork;
		second_fork = philos->right_fork;
	}
	else
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	pthread_mutex_lock(&second_fork->mutex);
	if (ft_routine_control(philos) == 1)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		pthread_mutex_unlock(&second_fork->mutex);
		return (1);
	}
	return (0);
}

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	if (philos->id % 2 == 0)
		usleep(philos->data->time_to_eat * 500);
	while (ft_routine_control(philos) == 0)
	{
		if (ft_take_forks(philos) == 1)
			break ;
		if (ft_eat(philos) == 1)
		{
			pthread_mutex_unlock(&philos->left_fork->mutex);
			pthread_mutex_unlock(&philos->right_fork->mutex);
			break ;
		}
		pthread_mutex_unlock(&philos->right_fork->mutex);
		pthread_mutex_unlock(&philos->left_fork->mutex);
		if (ft_sleep_think(philos) == 1)
			break ;
	}
	return (NULL);
}
