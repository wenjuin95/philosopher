/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/04/05 15:33:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_table *table, char **av);

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_output("wrong argument\n");
	check_digit(av);
	parse_input(&table, av);
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
	if (table->num_philo < 2)
		error_output("number of philo must be above 2\n");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_output("time must be above 60ms\n");
}