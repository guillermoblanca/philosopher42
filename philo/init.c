/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:51:09 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/21 13:05:03 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	error_params(t_table *table, const char *msg)
{
	printf("%s%s%s\n",
		RED, msg, RESET);
	free(table);
	exit(EXIT_FAILURE);
}

static int	create_forks(t_table *table)
{
	int				index;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philosopers);
	if (!table->forks)
		return (FALSE);
	index = 0;
	while (index < table->number_philosopers)
	{
		pthread_mutex_init(&table->forks[index], NULL);
		index++;
	}
	return (TRUE);
}

void	free_table(t_table *table)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < table->number_philosopers)
	{
		p = table->philoshophers[i];
		pthread_join(p->thread, NULL);
		pthread_mutex_destroy(&p->lock);
		pthread_mutex_destroy(&table->forks[i]);
		free(table->philoshophers[i]);
		i++;
	}
	free(table->philoshophers);
	free(table->forks);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->checker);
	free(table);
}

static void	create_mutex(t_table *table)
{
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->checker, NULL);
}

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		printf("%sError memory table%s\n", RED, RESET);
		return (NULL);
	}
	table->number_philosopers = ft_atoi(argv[1]);
	if (table->number_philosopers <= 0 || table->number_philosopers > 200)
		return (error_params(table, ERROR_NBR), NULL);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (table->time_to_die <= 0 || table->time_eat <= 0
		|| table->time_sleep <= 0)
		return (error_params(table, ERROR_PRM), NULL);
	table->nb_of_eat_philo = 0;
	table->philoshophers = NULL;
	table->simulation_active = TRUE;
	table->can_start = FALSE;
	table->start_time = get_time();
	if (argc == 6)
	{
		table->nb_of_eat_philo = ft_atoi(argv[5]);
		if (table->nb_of_eat_philo <= 0)
		{
			printf("%sError setting parameters\n%s", RED, RESET);
			free(table);
			return (NULL);
		}
	}
	create_mutex(table);
	create_forks(table);
	create_philosophers(table);
	return (table);
}
