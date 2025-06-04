/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine(WiP).c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:45:35 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/04 15:02:02 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

int	ft_routine_control(t_philo *philos)
{
	int	flag;

	flag = 0;
	if (philos->data->simulation_end == 1)
		flag = 1;
	return (flag);
}
// exit strategy is important with exit() and kill()
void	ft_philosopher_routine(t_philo *philos)
{
	if (philos->id % 2 == 0)
		usleep(philos->data->time_to_eat * 500);
	while (ft_routine_control(philos) == 0)
	{
		sem_wait(philos->data->sem_forks);
		sem_wait(philos->data->sem_forks);
		if (ft_eat(philos) == 1)
		{
			sem_post(philos->data->sem_forks);
			sem_post(philos->data->sem_forks);
			ft_error_handler();
		}
		sem_post(philos->data->sem_forks);
		sem_post(philos->data->sem_forks);
		if (ft_sleep_think(philos) == 1)
			ft_error_handler();
	}
	exit(0);
}
