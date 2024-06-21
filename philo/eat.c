/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:21:05 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/21 11:54:05 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	philo_msg(philo, LFORK_MSG);
	pthread_mutex_lock(&philo->table->forks[(philo->id + 1)
		% philo->table->number_philosopers]);
	philo_msg(philo, RFORK_MSG);
}

void	eat_behaviour(t_philo *philo)
{
	long	time;

	get_forks(philo);
	philo_msg(philo, EAT_MSG);
	pthread_mutex_lock(&philo->lock);
	philo->eating = TRUE;
	philo->meals_eaten++;
	philo->time_to_die = get_next_die(philo->table);
	time = get_eating_time(philo->table);
	pthread_mutex_unlock(&philo->lock);
	while (time > get_current_time(philo->table))
	{
		if (can_continue(philo->table) == FALSE)
			break ;
		usleep(1);
	}
	pthread_mutex_lock(&philo->lock);
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1)
		% philo->table->number_philosopers]);
}
