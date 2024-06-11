/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca- <gblanca-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-07 11:00:54 by gblanca-          #+#    #+#             */
/*   Updated: 2024-06-07 11:00:54 by gblanca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void*	philo_behaviour(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(10000);
		printf("%sPhilosopher %d%s behaviour!\n",
			get_text_color(philo->id % COLOR_LEN), philo->id, RESET);
	}
	return (NULL);
}

static void	create_philo(t_table *table, int id)
{
	t_philo		*philo;
	pthread_t	thread_id;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		free_philosophers(table, id);
	}
	philo->id = id;
	philo->eating = FALSE;
	philo->meals_eaten = FALSE;
	philo->can_start = FALSE;
	philo->last_meal = FALSE;
	if (pthread_create(&thread_id, NULL, philo_behaviour, philo) != 0)
	{
		printf("%sError creatint thread for philo %d\n%s"
			, RED, id, RESET);
		free_philosophers(table,id);
	}

}

void create_philosophers(t_table *table)
{
	int	philo_id;

	philo_id = 0;
	while (philo_id != table->number_philosopers)
	{
		create_philo(table, philo_id++);
	}
}

