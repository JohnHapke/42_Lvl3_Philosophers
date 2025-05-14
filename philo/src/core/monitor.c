/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:56:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/14 11:40:39 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor_routine(void *args)
{
	t_philo	*philos;
	int		dead_philo;

	philos = (t_philo *)args;
	while (1)
	{
		dead_philo = ft_monitor_time(philos);
		if (dead_philo >= 0)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			philos->data->simulation_end = 1;
			pthread_mutex_unlock(&philos->data->print_mutex);
			ft_print_status(&philos[dead_philo], R_DEAD);
			break ;
		}
		if (ft_monitor_meals(philos) == 1)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			philos->data->simulation_end = 1;
			pthread_mutex_unlock(&philos->data->print_mutex);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

int	ft_monitor_time(t_philo *philos)
{
	long long	time_last_meal;
	int			i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].mutex_last_meal);
		time_last_meal = ft_get_current_time() - philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].mutex_last_meal);
		if (time_last_meal > philos->data->time_to_die)
			return (i);
	}
	return (0);
}

int	ft_monitor_meals(t_philo *philos)
{
	int	i;
	int	j;
	int	flag_meals_eaten;

	i = -1;
	j = 0;
	flag_meals_eaten = 0;
	if (philos->data->meals_required <= 0)
		return (flag_meals_eaten);
	while (++i < philos->data->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].mutex_meals);
		if (philos[i].meals == philos->data->meals_required)
			j++;
		pthread_mutex_unlock(&philos[i].mutex_meals);
	}
	if (j == philos->data->num_of_philo)
		flag_meals_eaten = 1;
	return (flag_meals_eaten);
}
