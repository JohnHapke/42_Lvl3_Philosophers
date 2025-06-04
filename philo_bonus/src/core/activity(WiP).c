/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity(WiP).c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:46:27 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/04 14:48:46 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

int	ft_sleep_think(t_philo *philos)
{
	ft_print_status(philos, R_SLEEP);
	ft_exact_time(philos->data->time_to_sleep);
	ft_print_status(philos, R_THINK);
	return (ft_routine_control(philos));
}
// meals have to be supervised finished with exit() and/or kill()

int	ft_eat(t_philo *philos)
{
	if (ft_routine_control(philos) == 1)
		return (1);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_FORK);
	ft_print_status(philos, R_EAT);
	philos->last_meal = ft_get_current_time();
	philos->meals += 1;
	ft_exact_time(philos->data->time_to_eat);
	return (ft_routine_control(philos));
}
