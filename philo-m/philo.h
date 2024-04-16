/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:21 by welow             #+#    #+#             */
/*   Updated: 2024/04/16 14:05:58 by welow            ###   ########.fr       */
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
# define FLAG_OFF 0
# define FLAG_ON 1
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define EAT "\033[0;32mis eating\033[0m"

typedef struct s_philo
{
	int				num_philo;
	int				philo_id;
	int				eating;
	int				num_meal;
	long			last_meal;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			time_start_eat;
	int				num_for_philo_eat;
	int				*done_or_die;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				done_or_die;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_table;

//utils.c
void	destroy_all_mutex(t_table *table);
void	error_output(const char *str);
long	ft_atol(const char *str);
void	check_digit(char **av);

//philo.c
void	check_input(char **av);
void	init_table(t_table *table, char **av);
void	init_fork(t_table *table);
void	init_philo(t_table *table, char **av);

//start_table.c
int		philo_done_die(t_philo *philo);
void	*philo_move(void *arg);
void	start_table(t_table *table);

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
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

#endif