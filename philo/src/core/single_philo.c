/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:23:42 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/21 19:11:33 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_handle_single_philo(t_data *data)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
	{
		ft_error_handler(data, NULL, NULL, E_MEM);
		return (1);
	}
	pthread_mutex_init(&fork->mutex, NULL);
	ft_init_time(data);
	pthread_mutex_lock(&fork->mutex);
	printf("%lld %d has taken a fork\n", ft_elapsed_time(data), 1);
	pthread_mutex_unlock(&fork->mutex);
	usleep(data->time_to_die * 1000);
	pthread_mutex_lock(&fork->mutex);
	printf("%lld %d died\n", ft_elapsed_time(data), 1);
	pthread_mutex_unlock(&fork->mutex);
	pthread_mutex_destroy(&fork->mutex);
	free (fork);
	free (data);
	return (0);
}
