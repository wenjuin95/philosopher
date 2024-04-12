/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/04/12 10:08:48 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_input(char **av);
void	init_table(t_table *table, t_philo *philos);
void	init_fork(pthread_mutex_t *fork, char **av);
void	init_philo(t_table *table, t_philo *philos, pthread_mutex_t *fork,
			char **av);

// int	main(int ac, char **av)
// {
// 	t_table			table;
// 	t_philo			philos[200];
// 	pthread_mutex_t	fork[200];

// 	if (ac < 5 || ac > 6)
// 		error_output("wrong argument\n");
// 	check_digit(av);
// 	check_input(av);
// 	init_table(&table, philos);
// 	init_philo(&table, philos, fork, av);
// 	init_fork(fork, av);
// 	start_table(&table, fork);
// 	destroy_all_mutex(&table, fork);
// }
int	main(int ac, char **av)
{
	t_table			table;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	int				num_philo;

	if (ac < 5 || ac > 6)
		error_output("wrong argument\n");
	check_digit(av);
	check_input(av);
	num_philo = ft_atol(av[1]);
	philos = malloc(sizeof(t_philo) * num_philo + 1); //+1 because the philo start from 1
	if (philos == NULL)
		error_output("malloc failed\n");
	fork = malloc(sizeof(pthread_mutex_t) * num_philo + 1);
	if (fork == NULL)
		error_output("malloc failed\n");
	init_table(&table, philos);
	init_philo(&table, philos, fork, av);
	init_fork(fork, av);
	start_table(&table, fork);
	destroy_all_mutex(&table, fork);
	free(philos);
	free(fork);
}

void	check_input(char **av)
{
	if (ft_atol(av[1]) < 2 || ft_atol(av[1]) > 200)
		error_output("number of philo must be above 2 and not more than 200\n");
	if (ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60
		|| ft_atol(av[4]) < 60)
		error_output("time must be above 60ms\n");
	if (av[5] != NULL && ft_atol(av[5]) < 1)
		error_output("number of meal must be above 1\n");
}

void	init_table(t_table *table, t_philo *philos)
{
	table->done_or_die = 0;
	table->philo = philos;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
}

void	init_fork(pthread_mutex_t *fork, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
		pthread_mutex_init(&fork[i], NULL);
}

void	init_philo(t_table *table, t_philo *philos, pthread_mutex_t *fork,
	char **av)
{
	int	i;
	int	num_philo;

	num_philo = ft_atol(av[1]);
	i = -1;
	while (++i < num_philo)
	{
		assign_value(&philos[i], av);
		philos[i].philo_id = i + 1;
		philos[i].eating = 0;
		philos[i].num_meal = 0;
		philos[i].time_start_eat = get_time();
		philos[i].last_meal = get_time();
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].die = &table->done_or_die;
		philos[i].left_fork = &fork[i];
		if (i == 0)
			philos[i].right_fork = &fork[philos[i].num_philo - 1];
		else
			philos[i].right_fork = &fork[i - 1];
	}
}
