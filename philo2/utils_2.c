/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:40:05 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 17:40:05 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//this function is to wait for the time given
int	ft_usleep(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
	return (0);
}

//this function is to print the time, philo id and the string of each philo
/*
*	1. 200 is 200ms = 0.2s
*	2. 0 is false
*/
void	philo_say(char *str, t_philo *philo, int id)
{
	int	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->time_start_eat;
	if (philo_done_die(philo) == 0)
		printf("%d %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

//(time.tv_sec * 1000) + (time.tv_usec / 1000) convert microsec to millisec
//sec->milisec->microsec
int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	assign_value(t_philo *philo, char **av)
{
	philo->num_philo = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		philo->num_for_philo_eat = ft_atol(av[5]);
	else
		philo->num_for_philo_eat = -1;
}
