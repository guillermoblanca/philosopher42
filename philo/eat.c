/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:21:05 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/20 11:08:35 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_boolean	can_eat(t_philo *philo)
{
	//if (philo->meals_eaten < philo->table->nb_of_eat_philo && philo->eating == FALSE)
	if (philo->eating == FALSE)
		return (TRUE);
	return (FALSE);
}

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
	if (can_eat(philo) == FALSE)
		return ;
	get_forks(philo);
	philo_msg(philo, EAT_MSG);
	philo->eating = TRUE;
	philo->meals_eaten++;
	while (philo->time_eating >= get_current_time(philo->table))
	{
		if (is_philo_death(philo) == TRUE)
		{
			philo_msg(philo, DIE_MSG);
			set_alive_state(philo, FALSE);
			break ;
		}
		usleep(1);
	}
	philo->eating = FALSE;
	philo->time_eating = get_eating_time(philo->table);
	philo->time_to_die = get_next_die(philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1)
		% philo->table->number_philosopers]);
}