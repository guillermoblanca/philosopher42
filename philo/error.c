/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca- <gblanca-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-07 11:05:20 by gblanca-          #+#    #+#             */
/*   Updated: 2024-06-07 11:05:20 by gblanca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_philosophers(t_table *table, int failed_philo)
{
	printf("%sTODO: free philos!failed id %d\n%s", RED,
		failed_philo, RESET);
	free_table(table);
}