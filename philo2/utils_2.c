/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:08:34 by welow             #+#    #+#             */
/*   Updated: 2024/04/10 15:08:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}

// function for get time in milisecond
/*
*	sec * 1000 : convert second to milisecond
*	usec / 1000 : convert microsecond to milisecond
*	return the time in milisecond
*/
int	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// function is used to sleep for a certain amount of time for the philo
/*
*	(get_time() - start) < time) : check if the time passed is 
									less than the time given
*	philo_finish(philos) == 0 : check if the philo is not finish
*/
void	ft_usleep(int time, t_philo *philos)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time && philo_finish(philos))
		usleep(time / 10);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mutex);
	free(table->fork);
	free(table->philo);
	free(table);
}
