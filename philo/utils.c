/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:06:47 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/21 14:37:45 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*get_text_color(int id)
{
	id = id % 8;
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
	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_lock(&philo->table->checker);
	if (philo->table->simulation_active == TRUE)
	{
		printf("%s%zu %s %d %s%s\n", GREEN,
			get_current_time(philo->table), get_text_color(philo->id),
			philo->id + 1, str, RESET);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_unlock(&philo->table->checker);
}

t_boolean	is_philo_death(t_philo *philo)
{
	t_boolean	result;

	result = FALSE;
	pthread_mutex_lock(&philo->lock);
	if (get_current_time(philo->table)
		>= philo->time_to_die)
	{
		philo_msg(philo, DIE_MSG);
		result = TRUE;
	}
	pthread_mutex_unlock(&philo->lock);
	return (result);
}

void	set_alive_state(t_philo *philo, t_boolean state)
{
	pthread_mutex_lock(&philo->lock);
	philo->is_alive = state;
	pthread_mutex_unlock(&philo->lock);
}

t_boolean	can_continue(t_table *table)
{
	t_boolean	result;

	pthread_mutex_lock(&table->checker);
	result = table->simulation_active;
	pthread_mutex_unlock(&table->checker);
	return (result);
}

t_boolean	can_start(t_table *table)
{
	t_boolean	result;

	pthread_mutex_lock(&table->checker);
	result = table->can_start;
	pthread_mutex_unlock(&table->checker);
	return (result);
}

void	set_start(t_table *table, t_boolean state)
{

	pthread_mutex_lock(&table->checker);
	table->can_start = state;
	pthread_mutex_unlock(&table->checker);
}

void	set_continue(t_table *table, t_boolean state)
{
	pthread_mutex_lock(&table->checker);
	table->simulation_active = state;
	pthread_mutex_unlock(&table->checker);
}

void	debug_philo(t_philo *philo)
{
	printf("%s[%zu]ms philo:%d time to die:[%zu] is eating [%hhu] nb of meals %d %s\n", get_text_color(philo->id),
		get_current_time(philo->table), philo->id + 1, philo->time_to_die, philo->eating, philo->meals_eaten, RESET);
}
