/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/04/16 12:00:36 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	check_input(char **av)
{
	check_digit(av);
	if (ft_atol(av[1]) < 1 || ft_atol(av[1]) > 200)
		error_output("number of philo must be 1 or not more than 200\n");
	if (ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60
		|| ft_atol(av[4]) < 60)
		error_output("time must be above 60ms\n");
	if (av[5] != NULL && ft_atol(av[5]) < 1)
		error_output("number of meal must be above 1\n");
}

//function is to initialize table mutex(locker)
void	init_table(t_table *table, char **av)
{
	table->num_philo = ft_atol(av[1]);
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		error_output("malloc failed\n");
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (table->fork == NULL)
		error_output("malloc failed\n");
	table->done_or_die = FLAG_OFF;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
}

//function is to assign al value to philo struct
/*
*	1. philo_id: id of philo (+1 to avoid 0)
*	2. i == 0 is the first philo, so right fork will be the last philo fork
*	else, right fork will be the previous philo fork
*	3. each philo will have their own left fork and right fork
*/
void	init_philo(t_table *table, char **av)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		table->philo[i].num_philo = table->num_philo;
		assign_value(&table->philo[i], av);
		table->philo[i].philo_id = i + 1;
		table->philo[i].eating = FLAG_OFF;
		table->philo[i].num_meal = 0;
		table->philo[i].time_start_eat = get_time();
		table->philo[i].last_meal = get_time();
		table->philo[i].write_lock = &table->write_lock;
		table->philo[i].dead_lock = &table->dead_lock;
		table->philo[i].meal_lock = &table->meal_lock;
		table->philo[i].done_or_die = &table->done_or_die;
		table->philo[i].left_fork = &table->fork[i];
		if (i == 0)
			table->philo[i].right_fork = &table->fork
			[table->philo[i].num_philo - 1];
		else
			table->philo[i].right_fork = &table->fork[i - 1];
	}
}

//function is to give each philo fork a mutex(locker)
void	init_fork(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
		pthread_mutex_init(&table->fork[i], NULL);
}

int	main(int ac, char **av)
{
	t_table			table;

	if (ac < 5 || ac > 6)
		error_output("wrong argument\n");
	check_input(av);
	init_table(&table, av);
	init_philo(&table, av);
	init_fork(&table);
	start_table(&table);
	destroy_all_mutex(&table);
	free(table.philo);
	free(table.fork);
}