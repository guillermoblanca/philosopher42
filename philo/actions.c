/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:00:54 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/18 16:33:08 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


static void	sleep_behaviour(t_philo *philo)
{
	pthread_mutex_lock(philo->table->write_lock);
	philo_msg(philo, SLEEP_MSG);
	pthread_mutex_unlock(philo->table->write_lock);
	usleep(to_microseconds(philo->table->time_sleep));
}

static void	think_behaviour(t_philo *philo)
{
	int	time_to_think;
	int	time_to_eat;

	pthread_mutex_lock(philo->table->write_lock);
	philo_msg(philo, THINK_MSG);
	pthread_mutex_unlock(philo->table->write_lock);
	time_to_eat = philo->table->time_eat;
	time_to_think = (philo->table->time_to_die - (get_time()
				- philo->next_meal) - time_to_eat) / 2;
	usleep(to_microseconds(time_to_think));
}

static void	*philo_behaviour(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->table->can_start == FALSE)
		usleep(1);
	philo->next_meal = get_next_meal(philo->table);
	if (philo->id % 2 == 0)
		usleep(300);
	while (philo->is_alive == TRUE)
	{
		if (can_eat(philo) == TRUE)
		{
			eat_behaviour(philo);
			sleep_behaviour(philo);
			think_behaviour(philo);
		}
		else if (philo->eating == FALSE)
		{
			if (get_time() <= philo->time_to_die)
				sleep_behaviour(philo);
			else
			{
				pthread_mutex_lock(philo->death);
				philo->is_alive = FALSE;
				pthread_mutex_unlock(philo->death);
				pthread_mutex_unlock(philo->table->write_lock);
				pthread_mutex_lock(philo->table->write_lock);
				philo_msg(philo, DIE_MSG);
				pthread_mutex_unlock(philo->table->write_lock);
			}
		}
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
	philo->next_meal = get_next_meal(table);
	philo->time_to_die = get_next_die(table);
	philo->table = table;
	if (pthread_create(&thread_id, NULL, philo_behaviour, philo) != 0)
	{
		printf("%sError creating thread for philo %d\n%s",
			RED, id, RESET);
		free_philosophers(table, id);
	}
	philo->death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->death, NULL);
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
