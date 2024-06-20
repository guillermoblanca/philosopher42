/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gblanca <gblanca-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:55:17 by gblanca-          #+#    #+#             */
/*   Updated: 2024/06/18 14:35:59 by gblanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

//COLORS

# define GRAY "\x1b[90m"
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

//MESSAGES

# define SLEEP_MSG "is sleeping"
# define LFORK_MSG "has taken left fork"
# define RFORK_MSG "has taken rigth fork"
# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define DIE_MSG "has died"

typedef unsigned char	t_boolean;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	size_t			time_eating;
	size_t			time_to_die;
	t_boolean		eating;
	t_boolean		is_alive;
	t_boolean		meals_eaten;
	pthread_mutex_t	*lock; //lock de los datos del filosofo
	t_table			*table;
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
	t_boolean		simulation_active;
	t_philo			*philoshophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_lock; //usado para escribir con el printf
	pthread_mutex_t	*checker; //se usa para bloquear el acceso a data simulation_active
}	t_table;

//Initialize
t_table		*create_table(int argc, char **argv);
void		create_philosophers(t_table *table);

//Time
size_t		get_time(void);
size_t		get_eating_time(t_table *table);
size_t		get_next_die(t_table *table);
size_t		get_current_time(t_table *table);
//Utils
char		*get_text_color(int id);
int			ft_atoi(const char *str);
void		philo_msg(t_philo *philo, char *str);
size_t		to_microseconds(size_t ms);

//philosopher behaviour
t_boolean	can_eat(t_philo *philo);
t_boolean	is_philo_death(t_philo *philo);
void		eat_behaviour(t_philo *philo);

//Memory managemment

void		free_table(t_table *table);
void		free_philosophers(t_table *table, int failed_philo);
#endif