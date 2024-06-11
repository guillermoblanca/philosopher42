/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca- <gblanca-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-07 10:51:09 by gblanca-          #+#    #+#             */
/*   Updated: 2024-06-07 10:51:09 by gblanca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_nb_philosophers(t_table *table)
{
	printf("%sError: philosophers requires to be between 1-200%s\n"
		, RED, RESET);
	free_table(table);
	exit(EXIT_FAILURE);
}

void	free_table(t_table *table)
{
	free(table);
}

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		printf("%sError memory table%s\n", RED, RESET);
		exit(EXIT_FAILURE);
	}
	table->number_philosopers = ft_atoi(argv[1]);
	if (table->number_philosopers == 0 || table->number_philosopers > 200)
		check_nb_philosophers(table);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->nb_of_eat_philo = 1;
	table->philoshophers = NULL;
	table->forks = NULL;
	table->write_lock = NULL;
	table->meal_lock = NULL;
	table->has_died = FALSE;
	if (argc == 6)
		table->nb_of_eat_philo = ft_atoi(argv[5]);
	create_philosophers(table);
	return (table);
}
