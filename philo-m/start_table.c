/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:23:25 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 17:23:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check if philo is dead or done eating
/*
*	note:
*	1. philo->done_or_die :: is a pointer to a variable
*	2. *philo->done_or_die :: is the value of the variable
*/
int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->done_or_die == FLAG_ON)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (FALSE);
}

//function that check which philo start eating first
/*
*	1. even philo wait for 10ms before start
*		a. purpose of 10ms delay is to make sure it have enough time to 
		   check if the other philo is dead or done eating
*/

void	*philo_move(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(10);
	while (philo_done_die(philo) == FALSE)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_say("is thinking", philo, philo->philo_id);
	}
	return (NULL);
}

/*
*	1. first thread is to check each of second thread condition
*		a. waiter that check if the philo is dead or done eating
*	2. second thread is give each philo movement
*		b. each of the philo movement
*/
void	start_table(t_table *table)
{
	int			i;
	pthread_t	check_philo;

	if (pthread_create(&check_philo, NULL, &check_philo_condition,
			table->philo) != 0)
		destroy_all_mutex(table);
	i = -1;
	while (++i < table->philo->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_move,
				&table->philo[i]) != 0)
			destroy_all_mutex(table);
	}
	if (pthread_join(check_philo, NULL) != 0)
		destroy_all_mutex(table);
	i = -1;
	while (++i < table->philo->num_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			destroy_all_mutex(table);
	}
}
