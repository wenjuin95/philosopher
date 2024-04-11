/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:21 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 19:40:24 by welow            ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_table;

//utils.c
void	destroy_all_mutex(t_table *table, pthread_mutex_t *fork);
void	error_output(const char *str);
int		ft_atol(const char *str);
void	check_digit(char **av);

//philo.c
void	check_input(char **av);
void	init_table(t_table *table, t_philo *philos);
void	init_fork(pthread_mutex_t *fork, char **av);
void	init_philo(t_table *table, t_philo *philos, pthread_mutex_t *fork,
			char **av);

//start_table.c
int		philo_done_die(t_philo *philo);
void	*philo_move(void *arg);
int		start_table(t_table *table, pthread_mutex_t *fork);

//utils_2.c
int		ft_usleep(int time);
void	philo_say(char *str, t_philo *philo, int id);
int		get_time(void);
void	assign_value(t_philo *philo, char **av);

//philo_condition.c
int		check_done_eating(t_philo *philo);
int		philo_die(t_philo *philo, int time_to_die);
int		check_dead(t_philo *philo);
void	*check_philo_condition(void *arg);

//philo_action.c
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

#endif