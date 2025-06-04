/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:01:24 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/04 14:44:14 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

int	ft_init_project(int argc, char **argv, t_data *data)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_required = -1;
	data->simulation_end = 0;
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	if ((data->num_of_philo < 1 || data->num_of_philo > 200)
		|| (data->time_to_die < 0) || (data->time_to_eat < 0)
		|| (data->time_to_sleep < 0) || (argc == 6 && data->meals_required < 1))
	{
		ft_error_handler(data, NULL, NULL, E_INIT);
		return (1);
	}
	data->sem_forks = sem_open("/philo_forks",
			O_CREAT | O_EXCL, 0644, data->num_of_philo);
	data->sem_simulation_end = sem_open("/philo_sim_end",
			O_CREAT | O_EXCL, 0644, 1);
	ft_init_time(data);
	return (0);
}

void	ft_init_time(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	data->simulation_time = current_time.tv_sec
		* 1000 + current_time.tv_usec / 1000;
}

t_philo	*ft_init_philos(t_data *data, int id)
{
	t_philo		*philos;

	philos = malloc(sizeof(t_philo));
	if (!philos)
		ft_error_handler(data, philos, E_MEM);
	data->sem_forks = sem_open("/philo_forks", 0);
	data->sem_simulation_end = sem_open("/philo_sim_end", 0);
	philos->id = id + 1;
	philos->meals = 0;
	philos->data = data;
	philos->last_meal = ft_get_current_time();
	return (philos);
}
