/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:48:32 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/04 14:44:35 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_project_handler(t_data *data)
{
	t_philo		*philos;
	pid_t		pid[data->num_of_philo];
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			philos = ft_init_philos(data, i);
			if (!philos)
			{
				ft_error_handler(data, NULL, E_MEM);
				exit(0);
			}
		}
	}
	ft_wait_for_childen(pid, data);
	// WiP
	ft_cleanup_mutex(data, philos);
	ft_cleanup_memory(data, philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		ft_error_handler(NULL, NULL, E_ARG);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_error_handler(NULL, NULL, E_MEM);
		return (1);
	}
	if (ft_init_project(argc, argv, data) == 1)
		return (1);
	if (data->num_of_philo == 1)
	{
		if (ft_handle_single_philo(data) == 1)
			return (1);
	}
	else if (ft_project_handler(data) == 1)
		return (1);
	return (0);
}
