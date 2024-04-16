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

//check each philo is dead or done eating
int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->done_or_die == FLAG_ON)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (SUCCESS);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (FAIL);
}

//function that check which philo start eating first
/*
*	1. even philo wait for the time to eat (after the odd philo eat)
*	2. check each philo is dead or done eating
*		a.each philo start eating, sleep and think
*/

void	*philo_move(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (philo_done_die(philo) == FAIL)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_say("is thinking", philo, philo->philo_id);
	}
	return (NULL);
}

/*
*	1. first thread is to check if philo is dead or done eating
*	2. second thread(depend on num of philo) is to start eat, sleep and think
*	note: pthread_create is to create a new thread
*	note: pthreaad_join is to wait for the thread to finish
*/
void	start_table(t_table *table)
{
	int			i;
	pthread_t	check_philo;

	if (pthread_create(&check_philo, NULL, &check_philo_condition,
			table->philo) != FAIL)
		destroy_all_mutex(table);
	i = -1;
	while (++i < table->philo->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_move,
				&table->philo[i]) != FAIL)
			destroy_all_mutex(table);
	}
	if (pthread_join(check_philo, NULL) != FAIL)
		destroy_all_mutex(table);
	i = -1;
	while (++i < table->philo->num_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != FAIL)
			destroy_all_mutex(table);
	}
}
