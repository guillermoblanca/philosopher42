/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:10:53 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/18 16:09:31 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor_behaviour(void *data)
{
	t_table	*table;
	int		index;
	size_t	eaten_philos;

	table = (t_table *)data;
	while (table->simulation_active == TRUE)
	{
		index = 0 ;
		eaten_philos = 0;
		while (index < table->number_philosopers)
		{
			pthread_mutex_lock(table->philoshophers[index].death);
			if (table->philoshophers[index].is_alive == FALSE)
			{
				table->simulation_active = FALSE;
				printf("Detectada muerte!\n");
			}
			else if (table->philoshophers[index].meals_eaten >= table->nb_of_eat_philo)
				eaten_philos++;
			pthread_mutex_unlock(table->philoshophers[index].death);
			index++;
		}
		if (eaten_philos == table->nb_of_eat_philo)
		{
			while (index == 0)
			{
				table->philoshophers[index].meals_eaten = 0;
				index--;
			}
		}
	}
	return (NULL);
}

void	create_monitor(t_table *table)
{
	pthread_create(&table->monitor_thread, NULL, monitor_behaviour, table);
}
