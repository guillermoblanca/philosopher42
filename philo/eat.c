/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:21:05 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/18 16:32:04 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_boolean	can_eat(t_philo *philo)
{
	if (philo->meals_eaten < philo->table->nb_of_eat_philo && philo->eating == FALSE)
		return (TRUE);
	return (FALSE);
}

void	eat_behaviour(t_philo *philo)
{
	pthread_mutex_lock(philo->table->forks[philo->id]);
//	pthread_mutex_lock(philo->table->write_lock);
	philo_msg(philo, LFORK_MSG);
	pthread_mutex_lock(philo->table->forks[(philo->id + 1)
		% philo->table->number_philosopers]);
	philo_msg(philo, RFORK_MSG);
	philo_msg(philo, EAT_MSG);
//	pthread_mutex_unlock(philo->table->write_lock);
	philo->eating = TRUE;
	philo->meals_eaten++;
	usleep(to_microseconds(philo->table->time_eat));
	philo->eating = FALSE;
	philo->next_meal = get_next_meal(philo->table);
	philo->time_to_die = get_next_die(philo->table);
	pthread_mutex_unlock(philo->table->forks[philo->id]);
	pthread_mutex_unlock(philo->table->forks[(philo->id + 1)
		% philo->table->number_philosopers]);
}