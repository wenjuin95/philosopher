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
int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->done_or_die == FLAG_ON)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

//function that check which philo start eating first
/*
*	1. even philo wait for 100ms before start
*	2. check each philo is dead or done eating (0 is mean false)
*	3. each philo start eating, sleep and think
*/

void	*philo_move(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (philo_done_die(philo) == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/*
*	1. first create a thread to check if philo is dead or done eating
*	2. create a thread for each philo to eat, sleep and think
*	3. join the check_philo thread
*	4. join all philo thread
*	in this 
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
