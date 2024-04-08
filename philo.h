/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:21 by welow             #+#    #+#             */
/*   Updated: 2024/04/08 16:14:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define FAIL 0
# define SUCCESS 1
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

typedef struct s_philo	t_philo;

/*
*	1. the number of philo
*	2. time to die for each philo
*	3. time to eat for each philo
*	4. time to sleep for each philo
*	5. number of philo to eat
* 	6. check either done eat or die
*	7. for the philo
*	8. for the fork
*	9. for the mutex
*	10. for the left fork
*	11. for the right fork
*/
typedef struct table
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_philo_eat;
	int					time_for_start_table;
	int					done_or_die;
	t_philo				*philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_table;

/*
*	1. philosopher id
*	2. number of meal does philo ate
*	3. check either philo is eating or not
*	4. last time philo ate
*	5. time to eat
*	6. time to sleep
*	7. time to die
*	8. thread id
*	9. table
*	10. left fork
*	11. right fork
*/
typedef struct s_philo
{
	int					philo_id;
	int					num_meal;
	int					eating;
	int					last_meal;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	pthread_t			thread_id;
	t_table				*table;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

void	error_output(const char *str);
void	philo_say(t_philo *philos, const char *str);
int		ft_atol(const char *str);
void	check_digit(char **av);

void	parse_input(t_table *table, char **av);
int		assign_mutex(t_table *table);
int		make_philo(t_table *table);

void	start_table(t_table *table);
void	philo_move(void *arg);

int		philo_fork(t_philo *philos);
int		philo_finish(t_philo *philos);

#endif