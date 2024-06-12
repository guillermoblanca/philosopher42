/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca- <gblanca-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-06 12:55:17 by gblanca-          #+#    #+#             */
/*   Updated: 2024-06-06 12:55:17 by gblanca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define BLACK "\x1B[30m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"
# define RESET "\x1B[0m"
# define TRUE 1
# define FALSE 0
# define COLOR_LEN 8

typedef unsigned char	t_boolean;

typedef struct s_table t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_boolean	eating;
	t_boolean	is_alive;
	t_boolean	meals_eaten;
	size_t		last_meal;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	t_boolean		can_start;
	int				number_philosopers;
	size_t			time_sleep;
	size_t			time_to_die;
	size_t			time_eat;
	size_t			time;
	size_t			nb_of_eat_philo;
	t_boolean		has_died;
	t_philo			*philoshophers;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}	t_table;

//Initialize
t_table		*create_table(int argc, char **argv);
void		create_philosophers(t_table *table);
//Utils

size_t		get_time(t_table *table);
char		*get_text_color(int id);
int			ft_atoi(const char *str);
void		philo_msg(t_philo *philo, char *str);
//Memory managemment

void		free_table(t_table *table);
void		free_philosophers(t_table *table, int failed_philo);
#endif