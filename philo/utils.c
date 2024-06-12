/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca- <gblanca-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-06 14:06:47 by gblanca-          #+#    #+#             */
/*   Updated: 2024-06-06 14:06:47 by gblanca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_time(t_table *table)
{
	size_t			ms;
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	ms = (timer.tv_sec * 1000LL) + (timer.tv_usec / 1000LL);
	if (table)
		return (ms - table->time);
	return (ms);
}

char	*get_text_color(int id)
{
	if (id == 0)
		return (WHITE);
	if (id == 1)
		return (BLACK);
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
	printf("%s[%zu]MS %sPHILO:[%d] %s%s\n",GREEN,
		get_time(philo->table), get_text_color(philo->id), philo->id, str, RESET);
}
