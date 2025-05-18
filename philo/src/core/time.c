/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:50:45 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/18 21:35:03 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_current_time(void)
{
	struct timeval	current_time;
	long long		time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_in_ms);
}

long long	ft_elapsed_time(t_data *data)
{
	return (ft_get_current_time() - data->simulation_time);
}

void	ft_exact_time(long long ms)
{
	long long	start;
	long long	current;
	
	start = ft_get_current_time();
	while (1)
	{
		current = ft_get_current_time();
		if ((current - start) >= ms)
			break ;
		usleep(100);
	}
}