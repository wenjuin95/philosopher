/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:21 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 00:55:24 by welow            ###   ########.fr       */
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

typedef struct s_philo
{
	int				num_philo;
	int				philo_id;
	int				eating;
	int				num_meal;
	int				last_meal;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				time_start_eat;
	int				num_for_philo_eat;
	int				*die;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_table
{
	int				done_or_die;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
}	t_table;

void	error_output(const char *str);
int		ft_atol(const char *str);
void	check_digit(char **av);
// void	philo_say(t_philo *philos, const char *str);
// void	join_thread(t_table *table);
// int		get_time(void);
// void	ft_usleep(int time, t_philo *philos);
// void	free_all(t_table *table);

t_philo	parse_input(char **av);
// void	make_fork(t_philo *philo, )
// void	make_philo(t_table *table);
#endif