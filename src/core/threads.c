/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:19:59 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/09 10:34:44 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

Funktion ft_monitor_routine(void *args):
    - Cast args zu einem t_data* oder anderen passenden Typ
    - In einer Schleife, solange simulation_end == 0:
        - Für jeden Philosophen prüfen:
            - Ist die Zeit seit der letzten Mahlzeit > time_to_die?
                - Wenn ja: Setze simulation_end = 1 und gib Tod aus
            - Hat der Philosoph genug gegessen (wenn meals_required gesetzt)?
                - Zähle Philosophen, die genug gegessen haben
                - Wenn alle genug: Setze simulation_end = 1
        - Kurze Pause (z.B. 1ms) um CPU-Last zu reduzieren
    - Return NULL (oder anderer Wert)

void	*ft_monitor_routine(void *args)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)args;
	while(philos->data->simulation_end == 0)
	{
		if (philos->last_meal > philos->data->time_to_die)
		{
			philos->data->simulation_end = 1;
			ft_print_status(philos, R_DEAD);
			break;
		}
		while (philos[i].meals == philos->data->meals_required)
			i++;
		if (i == philos->data->meals_required)
			simulation_end = 1;
		usleep(100);
	}
	return (NULL);
}

Funktion ft_join_threads(data, philos, threads):
    - Für jeden Philosophen-Thread: pthread_join
    - Für den Monitor-Thread: pthread_join
    - Gib Erfolg oder Fehler zurück

Funktion ft_cleanup(data, philos):
    - Zerstöre alle Mutexe
    - Gib allen allokierten Speicher frei

void	ft_create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(data->philos[i].thread, NULL,
				ft_philosopher_routine, &data->philos[i] != 0))
			ft_error_handler();
		if (pthread_creat(&monitor, NULL,
				ft_monitor_routine, &data->philos[i] != 0))
			ft_error_handler();
	}
}
