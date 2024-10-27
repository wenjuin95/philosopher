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

/**
 * @brief check if philo is dead or done eating from "check_philo_condition"
 * @param philo: the philo struct
 * @return TRUE if philo is dead or done eating, FALSE if philo 
 * 		   not dead or done eating
 * @note 1. if no lock is used, the value of the variable can be 
 * 			changed in the middle
 * @note 2. *philo->done_or_die is the value of the variable
*/
int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_or_done_lock);
	if (*philo->done_or_die == FLAG_ON)
	{
		pthread_mutex_unlock(philo->dead_or_done_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_or_done_lock);
	return (FALSE);
}

/**
 * @brief philo movement function
 * @param arg: the param was casted to t_philo struct
 * @note 1. if philo id is even, wait for 1ms (make who start eating first)
 * @note 2. the "philo_done_die" flag is form check_philo_condition 
 * 			is true then the philo's will stop all movement
 * @note 3. philo will eat, sleep, and think
*/
void	philo_move(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 == 0)
		usleep_ms(3);
	while (philo_done_die(philo) == FALSE)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_say("is thinking", philo, philo->philo_id);
	}
}

/**
 * @brief create threads for "each philo" and "check philo condition"
 * @param table: get the philo struct from table
 * @note 1. if thread creation failed, destroy all mutex
 * @note 2. if thread join failed, destroy all mutex
 * @note 3. check_philo_condition thread is to check if philo
 * 			 is dead or done eating (it can be say as a waiter)
 * @note 4. philo_move thread is to give each philo movement
 * @note 5. pthread_create(pram1, pram2, pram3, pram4): create a thread
 * 			pram1: thread id
 * 			pram2: thread attribute (NULL for default)
 * 			pram3: function to run
 * 			pram4: argument to pass to the function
 * @note 6. pthread_join(pram1, pram2): wait for the thread to finish
 * 			pram1: thread id
 * 			pram2: return value from the thread
*/
void	start_table(t_table *table)
{
	int			i;
	pthread_t	check_philo;

	if (pthread_create(&check_philo, NULL, (void *)check_philo_condition,
			table->philo) != 0)
		destroy_all_mutex(table);
	i = -1;
	while (++i < table->philo->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, (void *)philo_move,
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
