/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:00:54 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/21 11:54:01 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	sleep_behaviour(t_philo *philo)
{
	long	sleep;

	philo_msg(philo, SLEEP_MSG);
	sleep = get_sleep_time(philo->table);
	while (sleep > get_current_time(philo->table))
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

static void	think_behaviour(t_philo *philo)
{
	long	time_to_think;

	philo_msg(philo, THINK_MSG);
	time_to_think = get_time_think(philo);
	while (time_to_think > get_current_time(philo->table))
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
	if (philo->id % 3 == 0)
		usleep(get_time_think(philo) * 1000);
	while (can_continue(philo->table) == TRUE)
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
	philo->time_to_die = get_next_die(table) - table->time_eat;
	philo->table = table;
	if (pthread_create(&thread_id, NULL, philo_behaviour, philo) != 0)
	{
		printf("%sError creating thread for philo %d\n%s",
			RED, id, RESET);
		free_philosophers(table, id);
	}
	philo->thread = thread_id;
	pthread_mutex_init(&philo->lock, NULL);
	table->philoshophers[id] = philo;
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
