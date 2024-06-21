/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:28:20 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/21 10:57:57 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(void)
{
	long			ms;
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	ms = (timer.tv_sec * 1000LL) + (timer.tv_usec / 1000LL);
	return (ms);
}

long	get_eating_time(t_table *table)
{
	return (get_current_time(table) + table->time_eat);
}

long	get_next_die(t_table *table)
{
	return (get_current_time(table) + table->time_to_die + table->time_eat);
}

long	get_current_time(t_table *table)
{
	return (get_time() - table->start_time);
}

long	get_sleep_time(t_table *table)
{
	return (get_current_time(table) + table->time_sleep);
}

long	get_time_think(t_philo *philo)
{
	return ((philo->time_to_die - (philo->table->time_eat)) / 2);
}