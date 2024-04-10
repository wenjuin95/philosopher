/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:07:18 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 00:55:05 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	// t_table			table;
	// t_philo			*philos;
	// pthread_mutex_t *fork;

	if (ac < 5 || ac > 6)
		error_output("wrong argument\n");
	check_digit(av);
	parse_input(av);
	// make_fork(&philos, fork);
	// make_philo();
}


t_philo	parse_input(char **av)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo));
	if (philos == NULL)
		error_output("malloc failed\n");
	philos->num_philo = ft_atol(av[1]);
	philos->time_to_die = ft_atol(av[2]);
	philos->time_to_eat = ft_atol(av[3]);
	philos->time_to_sleep = ft_atol(av[4]);
	printf("num_philo: %d\n", philos->num_philo);
	printf("time_to_die: %d\n", philos->time_to_die);
	printf("time_to_eat: %d\n", philos->time_to_eat);
	printf("time_to_sleep: %d\n\n", philos->time_to_sleep);
	if (av[5] != NULL)
	{
		philos->num_for_philo_eat = ft_atol(av[5]);
	}
	else
		philos->num_for_philo_eat = -1;
	if (philos->num_philo < 2 || philos->num_philo > 200)
		error_output("number of philo must be above 2 and not more than 200\n");
	if (philos->time_to_die < 60 || philos->time_to_eat < 60
		|| philos->time_to_sleep < 60)
		error_output("time must be above 60ms\n");
	return (philos);
}

/*
*	1. make a philo memory for each of the philo
*	note: assign the philo id (purpose of i+1 is to start from 1)
*	note: (i + 1) % table->num_philo is to make sure the last 
*		  philo can get the first fork
*/
// void	make_philo(t_philo *philo)
// {
// 	t_philo	*philos;
// 	int		i;

// 	i = 0;
// 	table->philo = malloc(sizeof(t_philo) * philo->num_philo);
// 	if (table->philo == NULL)
// 		return (NULL);
// 	while (i < philo->num_philo)
// 	{
// 		philos[i].philo_id = i + 1;
// 		philos[i].eating = 0;
// 		philos[i].num_meal = 0;
// 		philos[i].time_start_eat = get_current_time();
// 		philos[i].last_meal = get_current_time();
// 		philos[i].time_to_eat = philo->time_to_eat;
// 		philos[i].time_to_sleep = philo->time_to_sleep;
// 		philos[i].time_to_die = philo->time_to_die;
// 		philos[i].num_for_philo_eat = philo->num_of_philo_eat;
// 		philos[i].write_lock = &philo->write_lock;
// 		philos[i].dead_lock = &philo->dead_lock;
// 		philos[i].meal_lock = &philo->meal_lock;
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// void	make_fork(t_philo *philo, pthread_mutex_t *fork)
// {
// 	int				i;

// 	fork = malloc(sizeof(pthread_mutex_t) * philo->num_philo);
// 	if (fork == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < philo->num_philo)
// 	{
// 		pthread_mutex_init(&fork[i], NULL);
// 		i++;
// 	}
// }

