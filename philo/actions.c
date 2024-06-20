/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:00:54 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/20 11:43:27 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	sleep_behaviour(t_philo *philo)
{
	philo_msg(philo, SLEEP_MSG);
	
	usleep(to_microseconds(philo->table->time_sleep));
}

static void	think_behaviour(t_philo *philo)
{
	size_t	time_to_think;

	philo_msg(philo, THINK_MSG);
	time_to_think = (philo->time_to_die - (philo->time_eating)) / 2;
	if (philo->id % 2 == 0)
		time_to_think += 10;
	printf("Time to think for %d is %zu\n", philo->id, time_to_think);
	while (time_to_think >= get_current_time(philo->table))
	{
		if (is_philo_death(philo) == TRUE)
		{
			philo_msg(philo, DIE_MSG);
			set_alive_state(philo, FALSE);
			break ;
		}
		usleep(1);
	}
}

static void	*philo_behaviour(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (can_start(philo->table) == FALSE)
		usleep(1);
	if (philo->id % 2 == 0)
		usleep(300);
	philo->time_eating = get_eating_time(philo->table);
	philo->time_to_die  =get_next_die(philo->table);
	while (is_philo_death(philo) == FALSE && can_continue(philo->table) == TRUE)
	{
		eat_behaviour(philo);
		sleep_behaviour(philo);
		think_behaviour(philo);
	}
	return (NULL);
}

static void	create_philo(t_table *table, int id)
{
	t_philo		*philo;
	pthread_t	thread_id;

	if (!table)
		return ;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		free_philosophers(table, id);
	philo->id = id;
	philo->eating = FALSE;
	philo->meals_eaten = FALSE;
	philo->is_alive = TRUE;
	philo->time_eating = get_eating_time(table);
	philo->time_to_die = get_next_die(table);
	philo->table = table;
	if (pthread_create(&thread_id, NULL, philo_behaviour, philo) != 0)
	{
		printf("%sError creating thread for philo %d\n%s",
			RED, id, RESET);
		free_philosophers(table, id);
	}
	philo->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->lock, NULL);
	table->philoshophers[id] = *philo;
}

void	create_philosophers(t_table *table)
{
	int	philo_id;

	philo_id = 0;
	table->philoshophers = malloc (table->number_philosopers * sizeof(t_philo));
	if (table->philoshophers == NULL)
	{
		printf("%sError creating philosophers%s", RED, RESET);
		return ;
	}
	while (philo_id != table->number_philosopers)
	{
		create_philo(table, philo_id++);
	}
}
