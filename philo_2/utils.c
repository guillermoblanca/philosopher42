/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:06:47 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/18 11:46:03 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*get_text_color(int id)
{
	if (id == 0)
		return (WHITE);
	if (id == 1)
		return (GRAY);
	if (id == 2)
		return (RED);
	if (id == 3)
		return (GREEN);
	if (id == 4)
		return (YELLOW);
	if (id == 5)
		return (BLUE);
	if (id == 6)
		return (MAGENTA);
	if (id == 7)
		return (CYAN);
	return ("");
}

void	philo_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->table->write_lock);
	printf("%s[%zu] ms %sphilo %d %s%s\n", GREEN,
		get_current_time(philo->table), get_text_color(philo->id),
		philo->id, str, RESET);
	pthread_mutex_unlock(philo->table->write_lock);
}

t_boolean	is_philo_death(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (get_current_time(philo->table) >= philo->time_to_die || philo->is_alive == FALSE)
		return (TRUE);
	pthread_mutex_unlock(philo->lock);
	return (FALSE);
}

t_boolean	can_continue(t_table *table)
{
	
	table->simulation_active
}

size_t	to_microseconds(size_t ms)
{
	return (ms * 1000);
}

