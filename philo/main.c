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
int	main(int argc, char **argv)
{
	t_table		*table;
	long long	start;
	long long	end;

	table = malloc(sizeof(t_table));
	start = get_time();
	if (argc < 4 || argc > 6)
	{
		printf("%sERROR: Parameters are incorrect%s\n",RED, RESET);
		print_help();
		return (EXIT_FAILURE);
	}
	else
	{
		table = create_table(argc, argv);
		print_table(table);
		table->can_start = TRUE;
	}
	end = get_time();
	printf("TIME: %s%lld%s \n", GREEN, (end - start), RESET);
	while (table->simulation_active == TRUE)
	{
	}
	return (EXIT_SUCCESS);
}