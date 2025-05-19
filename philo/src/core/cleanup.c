/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:32:37 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/19 10:58:42 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_handler(t_data *data, t_philo *philos,
			t_fork *forks, t_error_code code)
{
	if (code == E_ARG)
		write (2, "Error: invalid number of arguments\n", 35);
	if (code == E_INIT)
		write(2, "usage: invalid argument(s)\n", 27);
	if (code == E_MEM)
		write(2, "Error: memory allocation error\n", 31);
	if (code == E_THREAD)
		write(2, "Error: thread operation failed\n", 31);
	ft_cleanup_mutex(data, philos, forks);
	ft_cleanup_memory(data, philos, forks);
}

void	ft_cleanup_mutex(t_data *data, t_philo *philos, t_fork *forks)
{
	int	i;

	i = -1;
	if (data)
	{
		pthread_mutex_destroy(&data->mutex_sim_end);
	}
	if (philos && philos->data)
	{
		while (++i < philos->data->num_of_philo)
		{
			pthread_mutex_destroy(&philos[i].mutex_last_meal);
			pthread_mutex_destroy(&philos[i].mutex_meals);
		}
	}
	i = -1;
	if (forks && philos && philos->data)
	{
		while (++i < philos->data->num_of_philo)
			pthread_mutex_destroy(&forks[i].mutex);
	}
}

void	ft_cleanup_memory(t_data *data, t_philo *philos,
			t_fork *forks)
{
	if (data)
		free (data);
	if (philos)
		free (philos);
	if (forks)
		free (forks);
}
