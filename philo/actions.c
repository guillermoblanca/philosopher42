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

static t_boolean	can_eat(t_philo *philo)
{
	if (philo->meals_eaten < philo->table->nb_of_eat_philo
		&& philo->last_meal <= get_time(philo->table))
		return (TRUE);
	return (FALSE);
}
static void*	philo_behaviour(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->table->can_start == FALSE)
		usleep(1);
	
	while (philo->is_alive == TRUE)
	{
		if(can_eat(philo) == TRUE)
		{
			pthread_mutex_lock(philo->table->forks[philo->id]);
			philo_msg(philo, "has taken left fork");
			pthread_mutex_lock(philo->table->forks[(philo->id + 1)
				% philo->table->number_philosopers]);
			philo_msg(philo, "has taken rigth fork");
			philo_msg(philo, "is eating");
			philo->eating = TRUE;
			philo->meals_eaten++;
			philo->last_meal = get_time(philo->table);
			usleep(philo->table->time_eat);
			pthread_mutex_unlock(philo->table->forks[philo->id]);
			pthread_mutex_unlock(philo->table->forks[(philo->id + 1)
				% philo->table->number_philosopers]);
		}
		else 
		{
			philo_msg(philo, "is sleeping");
			usleep(philo->table->time_sleep);
		}
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
	philo->is_alive = TRUE;
	philo->last_meal = FALSE;
	philo->table = table;
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

