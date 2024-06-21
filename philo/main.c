/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:19:02 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/21 10:48:49 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_table(t_table *table)
{
	printf("Table die:%s%zu%s\n", GREEN, table->time_to_die, RESET);
	printf("Table eat:%s%zu%s\n", GREEN, table->time_eat, RESET);
	printf("Table sleep:%s%zu%s\n", GREEN, table->time_sleep, RESET);
	printf("Table eat per filo:%s%zu%s\n",
		GREEN, table->nb_of_eat_philo, RESET);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (argc < 4 || argc > 6)
	{
		printf("%sERROR: Parameters are incorrect%s\n", RED, RESET);
		return (EXIT_FAILURE);
	}
	table = create_table(argc, argv);
	set_start(table, TRUE);
	print_table(table);
	while (can_continue(table) == TRUE)
	{
		int i = 0;
		int all_eat = 0;
		while (i < table->number_philosopers)
		{
			if (is_philo_death(table->philoshophers[i]) == TRUE)
			{
				debug_philo(table->philoshophers[i]);
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
			usleep(10000);
			i++;
		}
		if (all_eat == table->number_philosopers)
		{
			printf("All meals eaten\n");
			set_continue(table, FALSE);
		}
	}
	printf("Set clean\n");
	int i = 0;
		while (i < table->number_philosopers)
		{
			pthread_join(table->philoshophers[i]->thread, NULL);
			i++;
		}
	return (EXIT_SUCCESS);
}