/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:22:28 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/19 10:59:30 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *philos, t_routine_code code)
{
	pthread_mutex_lock(&philos->data->mutex_sim_end);
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
	else if (philos->data->simulation_end == 1 && code == R_DEAD)
		printf("%lld %d died\n", ft_elapsed_time(philos->data), philos->id);
	else if (code == R_ALL)
		printf("%lld maximum amount of meals eaten\n",
			ft_elapsed_time(philos->data));
	pthread_mutex_unlock(&philos->data->mutex_sim_end);
}
