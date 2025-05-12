/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:56:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/12 12:47:00 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor_routine(void *args)
{
	t_philo		*philos;
	int			i;
	int			time_control;
	int			meal_control;

	philos = (t_philo *)args;
	i = -1;
	while (1)
	{
		if (time_control == 1)
		{
			ft_print_status(philos, R_DEAD);
			break ;
		}
		if (meal_control == 1)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			philos->data->simulation_end = 1;
			pthread_mutex_unlock(&philos->data->print_mutex);
			break ;
		}
		usleep(100);
	}
}

int	ft_monitor_time(t_philo *philos)
{
	long long	time_last_meal;
	int			i;

	i = -1;
	while (++i < philos->data->num_of_philo)
	{
		time_last_meal = ft_get_current_time() - philos[i].last_meal;
		if (time_last_meal > philos->data->time_to_die)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			philos->data->simulation_end = 1;
			pthread_mutex_unlock(&philos->data->print_mutex);
			return (1);
		}
	}
	return (0);
}

int	ft_monitor_meals(t_philo *philos)
{
	int	i;
	int	flag_meals_eaten;

	i = -1;
	if (philos->data->meals_required > 0)
		flag_meals_eaten = 0;
	while (++i < philos->data->num_of_philo)
	{
		if (philos[i].meals == philos->data->meals_required)
		{
			flag_meals_eaten = 1;
			return (flag_meals_eaten);
		}
	}
	return (flag_meals_eaten);
}
