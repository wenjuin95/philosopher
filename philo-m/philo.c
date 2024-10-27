/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/10/27 22:18:49 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check all input and give error message if invalid
 * @param av: input arguments
 * @return 0 if valid, 1 if invalid
 * @note 1. check all nb is within INT_MAX
 * @note 2. check number of philo is between 1 and 200
 * @note 3. check time is at least 60ms
 * @note 4. check number of meal is at least 1
*/
int	check_input(char **av)
{
	check_digit(av);
	if (ft_atol(av[1]) >= INT_MAX || ft_atol(av[2]) >= INT_MAX
		|| ft_atol(av[3]) >= INT_MAX || ft_atol(av[4]) >= INT_MAX
		|| (av[5] != NULL && ft_atol(av[5]) >= INT_MAX))
	{
		printf("%sNumber is too big\n", RED);
		return (1);
	}
	if (ft_atol(av[1]) < 1 || ft_atol(av[1]) > 200)
	{
		printf("%sNumber of philo must be 1 or not more than 200\n", RED);
		return (1);
	}
	if (ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60
		|| ft_atol(av[4]) < 60)
	{
		printf("%sTime must be at least 60ms\n", RED);
		return (1);
	}
	if (av[5] != NULL && ft_atol(av[5]) < 1)
	{
		printf("%sNumber of meal must be at least 1\n", RED);
		return (1);
	}
	return (0);
}

/**
 * @brief initialize number of philo, philo struct, fork struct
 * 		  , set done and die flag, and initialize the movement locks
 * @param table: table struct
 * @param av: number of philo input
*/
void	init_table(t_table *table, char **av)
{
	table->num_philo = ft_atol(av[1]);
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		return ;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (table->fork == NULL)
		return ;
	table->done_or_die = FLAG_OFF;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->do_lock, NULL);
}

/** 
 * @brief initialize philo sturct
 * @param table: get the philo struct from table
 * @param av: input arguments
 * @note 1. if philo is the first philo, assign the right fork 
 * 			is last philo fork else assign the right fork is 
 * 			the previous philo fork
*/
void	init_philo(t_table *table, char **av)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		table->philo[i].num_philo = table->num_philo;
		table->philo[i].philo_id = i + 1;
		table->philo[i].eating = FLAG_OFF;
		table->philo[i].num_meal = 0;
		table->philo[i].time_start_eat = get_time_ms();
		table->philo[i].last_meal = get_time_ms();
		assign_time(&table->philo[i], av);
		table->philo[i].dead_lock = &table->dead_lock;
		table->philo[i].do_lock = &table->do_lock;
		table->philo[i].done_or_die = &table->done_or_die;
		table->philo[i].left_fork = &table->fork[i];
		if (i == 0)
			table->philo[i].right_fork = &table->fork
			[table->philo[i].num_philo - 1];
		else
			table->philo[i].right_fork = &table->fork[i - 1];
	}
}

/**
 * @brief set each philo a fork lock
 * @param table: get the fork lock from table	
*/
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
	{
		printf("%sInvalid number of arguments\n", RED);
		return (1);
	}
	if (check_input(av) == 1)
		return (1);
	init_table(&table, av);
	init_fork(&table);
	init_philo(&table, av);
	start_table(&table);
	destroy_all_mutex(&table);
	free(table.philo);
	free(table.fork);
	return (0);
}
