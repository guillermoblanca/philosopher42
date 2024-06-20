/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:19:02 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/18 16:27:56 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


static void	print_table(t_table *table)
{
	int	filos;

	filos = 0;
	while (filos < table->number_philosopers)
	{
		printf("%sPhilosopher %d%s hello!\n",
			get_text_color(filos % COLOR_LEN), filos, RESET);
		filos++;
	}
	printf("Table sleep:%s%zu%s\n",GREEN, table->time_sleep, RESET);
	printf("Table die:%s%zu%s\n",GREEN, table->time_to_die, RESET);
	printf("Table eat:%s%zu%s\n",GREEN, table->time_eat, RESET);
	printf("Table eat per filo:%s%zu%s\n",
		GREEN, table->nb_of_eat_philo, RESET);
}
static void print_help(void)
{
	printf("1. Number of philosophers\n");
	printf("2. time to die\n");
	printf("3. time to eat\n");
	printf("4. time to sleep\n");
	printf("5. [OPTIONAL] \n");
}

static void example(t_table *table, int argc, char **argv)
{
	table = create_table(argc, argv);
	print_table(table);
	table->can_start = TRUE;
	while (table->simulation_active == TRUE)
	{
	}
}
int	main(int argc, char **argv)
{
	t_table		*table;
	size_t	start;

	table = malloc(sizeof(t_table));
	start = get_time();
	if (argc < 4 || argc > 6)
	{
		printf("%sERROR: Parameters are incorrect%s\n",RED, RESET);
		print_help();
		return (EXIT_FAILURE);
	}
	table = create_table(argc, argv);
	table->can_start = TRUE;
	print_table(table);
	while (table->simulation_active == TRUE)
	{
		int i = 0;
		while ( i < table->number_philosopers)
		{
			pthread_mutex_lock(table->philoshophers[i].lock);
			if (table->philoshophers[i].is_alive == FALSE)
			{
				table->simulation_active = FALSE;
				printf("NOTIFIED\n");
			}
			pthread_mutex_unlock(table->philoshophers[i].lock);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}