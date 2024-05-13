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
/*
*	1. 500microsec = 0.5ms
*	2. purpose for 0.5ms is to make sure it have enough time for the 
*	   other philo to check if it is dead or done eating
*	note: usleep get precise timing in microsec
*	note: ft_usleep get precise timing in millisec
*   note: need ft_usleep because get_time() is in millisec
*/
int	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
	return (0);
}

//(time.tv_sec * 1000) + (time.tv_usec / 1000) convert microsec to millisec
//sec->milisec->microsec
/*
*	struct timeval is a struct that contains two members
*	1. tv_sec is the number of seconds
*	2. tv_usec is the number of microseconds
*/
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//this function is to print the time, philo id and the string of each philo
void	philo_say(char *str, t_philo *philo, int id)
{
	int	time;

	pthread_mutex_lock(philo->do_lock);
	time = get_time() - philo->time_start_eat;
	if (philo_done_die(philo) == FALSE)
	{
		printf("%d %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->do_lock);
}

//assign the time and the number of philo eat to philo struct
void	assign_time(t_philo *philo, char **av)
{
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		philo->num_for_philo_eat = ft_atol(av[5]);
	else
		philo->num_for_philo_eat = -1;
}
