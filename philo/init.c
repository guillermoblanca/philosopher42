/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:51:09 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/20 10:35:23 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_nb_philosophers(t_table *table)
{
	printf("%sError: philosophers requires to be between 1-200%s\n",
		RED, RESET);
	free_table(table);
	exit(EXIT_FAILURE);
}

static int	create_forks(t_table *table)
{
	int				index;
	pthread_mutex_t	*tmp;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philosopers);
	if (!table->forks)
		return (FALSE);
	index = 0;
	while (index < table->number_philosopers)
	{
		tmp = malloc(sizeof(pthread_mutex_t));
		if (!tmp)
			return (FALSE);
		pthread_mutex_init(tmp, NULL);
		table->forks[index] = *tmp;
		index++;
	}
	return (TRUE);
}

void	free_table(t_table *table)
{
	free(table);
}

static void	create_mutex(t_table *table)
{
	table->write_lock = malloc(sizeof(pthread_mutex_t));
	if (!table->write_lock)
		free_table(table);
	table->checker = malloc(sizeof(pthread_mutex_t));
	if (!table->checker)
	{
		free(table->write_lock);
		free_table(table);
	}
	pthread_mutex_init(table->write_lock, NULL);
	pthread_mutex_init(table->checker, NULL);
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
	table->simulation_active = TRUE;
	table->can_start = FALSE;
	table->start_time = get_time();
	if (argc == 6)
		table->nb_of_eat_philo = ft_atoi(argv[5]);
	create_mutex(table);
	create_philosophers(table);
	create_forks(table);
	return (table);
}
