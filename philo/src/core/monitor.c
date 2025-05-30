/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:56:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/21 18:35:03 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor_routine(void *args)
{
	t_philo	*philos;
	int		dead_philo;

	philos = (t_philo *)args;
	usleep(1000);
	while (1)
	{
		dead_philo = ft_monitor_time(philos);
		if (dead_philo >= 0)
		{
			ft_simulation_end_control(philos);
			ft_print_status(&philos[dead_philo], R_DEAD);
			break ;
		}
		if (ft_monitor_meals(philos) == 1)
		{
			ft_simulation_end_control(philos);
			ft_print_status(philos, R_ALL);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

int	ft_monitor_time(t_philo *philos)
{
	long long	time_since_last_meal;
	int			i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].mutex_meal_lock);
		time_since_last_meal = ft_get_current_time() - philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].mutex_meal_lock);
		if (time_since_last_meal > philos->data->time_to_die)
			return (i);
	}
	return (-1);
}

int	ft_monitor_meals(t_philo *philos)
{
	int	i;
	int	meals_count;
	int	flag_meals_eaten;

	if (philos->data->meals_required <= 0)
		return (0);
	i = -1;
	meals_count = 0;
	flag_meals_eaten = 1;
	while (++i < philos->data->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].mutex_meal_lock);
		meals_count = philos[i].meals;
		pthread_mutex_unlock(&philos[i].mutex_meal_lock);
		if (meals_count <= philos->data->meals_required)
		{
			flag_meals_eaten = 0;
			break ;
		}
	}
	return (flag_meals_eaten);
}
