/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:19:02 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/20 11:21:29 by gblanca          ###   ########.fr       */
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
	printf("2. start_time to die\n");
	printf("3. start_time to eat\n");
	printf("4. start_time to sleep\n");
	printf("5. [OPTIONAL] \n");
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (argc < 4 || argc > 6)
	{
		printf("%sERROR: Parameters are incorrect%s\n",RED, RESET);
		print_help();
		return (EXIT_FAILURE);
	}
	table = create_table(argc, argv);
	set_start(table, TRUE);
	print_table(table);
	while (can_continue(table) == TRUE)
	{
		int i = 0;
		while (i < table->number_philosopers)
		{
			if (is_philo_death(table->philoshophers) == TRUE)
			{
				set_continue(table, FALSE);
				printf("NOTIFIED\n");
				usleep(100);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}