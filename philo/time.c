/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:28:20 by gblanca           #+#    #+#             */
/*   Updated: 2024/06/20 10:35:23 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_time(void)
{
	size_t			ms;
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	ms = (timer.tv_sec * 1000LL) + (timer.tv_usec / 1000LL);
	return (ms);
}

size_t	get_eating_time(t_table *table)
{
	return (get_current_time(table) + table->time_eat);
}

size_t	get_next_die(t_table *table)
{
	return (get_current_time(table) + table->time_to_die);
}

size_t	get_current_time(t_table *table)
{
	return (get_time() - table->start_time);
}
