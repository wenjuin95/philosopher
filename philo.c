/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/04/08 15:23:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_table *table, char **av);
int		assign_mutex(t_table *table);
int		make_philo(t_table *table);

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_output("wrong argument\n");
	check_digit(av);
	parse_input(&table, av);
	start_table(&table);
}

/*
*  1. "* 1000" is to covert to milisecond
*/
void	parse_input(t_table *table, char **av)
{
	table->num_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5] != NULL)
	{
		table->num_of_philo_eat = ft_atol(av[5]);
	}
	else
		table->num_of_philo_eat = -1;
	if (table->num_philo < 2 || table ->num_philo > 200)
		error_output("number of philo must be above 2 and not more than 200\n");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_output("time must be above 60ms\n");
	table->done_or_die = 0;
	if (assign_mutex(table) == 0)
		error_output("mutex error\n");
	if (make_philo(table) == 0)
		error_output("philo error\n");
}

/*
*	1. make a fork lock memory for each of the philo
*	2. make a mutex lock memory for each of the philo
*	note: the "!= 0" in pthread_mutex_init is return 0 if success
*/
int	assign_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (table->fork == NULL)
		return (0);
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (FAIL);
		i++;
	}
	if (pthread_mutex_init(&table->mutex, NULL) != 0)
		return (FAIL);
	return (SUCCESS);
}

/*
*	1. make a philo memory for each of the philo
*	note: assign the philo id (purpose of i+1 is to start from 1)
*	note: (i + 1) % table->num_philo is to make sure the last 
*		  philo can get the first fork
*/
int	make_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		return (FAIL);
	while (i < table->num_philo)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].num_meal = 0;
		table->philo[i].eating = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].time_to_eat = table->time_to_eat;
		table->philo[i].time_to_sleep = table->time_to_sleep;
		table->philo[i].time_to_die = table->time_to_die;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->fork[i];
		table->philo[i].right_fork = &table->fork[(i + 1) % table->num_philo];
		i++;
	}
	return (SUCCESS);
}
