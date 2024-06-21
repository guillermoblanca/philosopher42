/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:19:02 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/21 13:08:28 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc > 6 || argc < 5)
	{
		printf("%s%s%s\n", RED, ERROR_PRM, RESET);
		return (EXIT_FAILURE);
	}
	table = create_table(argc, argv);
	if (table == NULL)
		return (EXIT_FAILURE);
	set_start(table, TRUE);
	while (can_continue(table) == TRUE)
	{
		int i = 0;
		int all_eat = 0;
		while (i < table->number_philosopers)
		{
			if (is_philo_death(table->philoshophers[i]) == TRUE)
			{
				set_continue(table, FALSE);
				break ;
			}
			else if (table->nb_of_eat_philo > 0)
			{
				pthread_mutex_lock(&table->philoshophers[i]->lock);
				if (table->philoshophers[i]->meals_eaten >= table->nb_of_eat_philo)
					all_eat++;
				pthread_mutex_unlock(&table->philoshophers[i]->lock);
			}
			usleep(2500);
			i++;
		}
		if (all_eat == table->number_philosopers)
			set_continue(table, FALSE);
	}
	free_table(table);
	return (EXIT_SUCCESS);
}
