/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:58:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/15 11:34:07 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *philos, t_routine_code code)
{
	pthread_mutex_lock(&philos->data->print_mutex);
	if (philos->data->simulation_end == 0 && code == R_SLEEP)
		printf("%lld %d is sleeping\n",
			ft_elapsed_time(philos->data), philos->id);
	else if (philos->data->simulation_end == 0 && code == R_THINK)
		printf("%lld %d is thinking\n",
			ft_elapsed_time(philos->data), philos->id);
	else if (philos->data->simulation_end == 0 && code == R_EAT)
		printf("%lld %d is eating\n",
			ft_elapsed_time(philos->data), philos->id);
	else if (philos->data->simulation_end == 0 && code == R_FORK)
		printf("%lld %d has taken a fork\n",
			ft_elapsed_time(philos->data), philos->id);
	else if (philos->data->simulation_end == 1 || code == R_DEAD)
		printf("%lld %d died\n", ft_elapsed_time(philos->data), philos->id);
	else if (code == R_ALL)
		printf("%lld maximum amount of meals eaten\n",
			ft_elapsed_time(philos->data));
	pthread_mutex_unlock(&philos->data->print_mutex);
}

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

void	*ft_philosopher_routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (ft_routine_control(philos) == 0)
	{
		if (ft_think(philos) == 1)
			break ;
		if (philos->left_fork->fork_id < philos->right_fork->fork_id)
		{
			pthread_mutex_lock(&philos->left_fork->mutex);
			if (ft_routine_control(philos) == 1)
			{
				pthread_mutex_unlock(&philos->left_fork->mutex);
				break ;
			}
			pthread_mutex_lock(&philos->right_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&philos->right_fork->mutex);
			if (ft_routine_control(philos) == 1)
			{
				pthread_mutex_unlock(&philos->right_fork->mutex);
				break ;
			}
			pthread_mutex_lock(&philos->left_fork->mutex);
		}
		if (ft_eat(philos) == 1)
			break ;
		pthread_mutex_unlock(&philos->right_fork->mutex);
		pthread_mutex_unlock(&philos->left_fork->mutex);
		if (ft_sleep(philos) == 1)
			break ;
	}
	return (NULL);
}
