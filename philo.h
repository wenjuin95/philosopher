/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:21 by welow             #+#    #+#             */
/*   Updated: 2024/04/05 15:35:29 by welow            ###   ########.fr       */
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

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

/*
*	1. fork locker
*	2. fork id
*/
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

/*
*	1. philo id
*	2. number of meal the philo have
*	3. last meal time for the philo
*	4. check is full?
*	5. left fork for philo
*	6. right fork for philo
*	7. thread id for philo (for each philo)
*/
typedef struct s_philo
{
	int				philo_id;
	long			num_meal;
	long			last_meal_time;
	int				philo_full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
}	t_philo;

/*
*	1. the number of philo
*	2. time to die for each philo
*	3. time to eat for each philo
*	4. time to sleep for each philo
*	5. number of philo to eat
* 	6. check either done eat or die
*	7. for a pair of fork
*	8. for the philo
*/
typedef struct table
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_philo_eat;
	long			time_for_start_table;
	int				done_or_die;
	t_fork			*pair_fork;
	t_philo			*philo;

}	t_table;

void	error_output(const char *str);
int		ft_atol(const char *str);
void	check_digit(char **av);

void	parse_input(t_table *table, char **av);

#endif