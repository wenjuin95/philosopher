/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:48:39 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 17:48:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check if philo is dead
 * @param philo: the philo struct
 * @param time_to_die: the time to die
 * @return TRUE if philo is dead, FALSE if philo is not dead
 * @note 1. if the current time - last meal time is more than
 * 			or equal to time to die and philo is not eating
 * @note 2. if no lock is used, the value of the variable can be in the middle
*/
int	philo_die(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->do_lock);
	if ((get_time_ms() - philo->last_meal) >= time_to_die
		&& philo->eating == FLAG_OFF)
	{
		pthread_mutex_unlock(philo->do_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->do_lock);
	return (FALSE);
}

/**
 * @brief check if philo is dead then print "died" and return the flag to
 * 		  "philo_move" to stop all philo movement
 * @param philo: the philo struct
 * @return TRUE if philo is dead, FALSE if philo is not dead
*/
int	check_dead(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_philo)
	{
		if (philo_die(&philo[i], philo[i].time_to_die) == TRUE)
		{
			philo_say("died", &philo[i], philo[i].philo_id);
			pthread_mutex_lock(philo->dead_lock);
			*philo->done_or_die = FLAG_ON;
			pthread_mutex_unlock(philo->dead_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

/**
 * @brief check if philo has finished eating
 * @param philo: the philo struct
 * @return TRUE if all philo has finished eating, FALSE if not
 * @note 1. if philo->num_for_philo_eat is -1, return FALSE because is a error
 * @note 2. if the number of meal that philo need to eat is equal to the number
 * 			of philo that has finished eating, increment the finish_eating
 * @note 3. if every philo get the same "finish_eating" value, return the flag
 * 			to "philo_move" to stop all philo movement
 * @note 4. if no lock is used, the value of the variable can be in the middle
*/
int	check_done_eating(t_philo *philo)
{
	int	i;
	int	finish_eating;

	i = -1;
	finish_eating = 0;
	if (philo->num_for_philo_eat == -1)
		return (FALSE);
	while (++i < philo->num_philo)
	{
		pthread_mutex_lock(philo->do_lock);
		if (philo[i].num_meal >= philo[i].num_for_philo_eat)
			finish_eating++;
		pthread_mutex_unlock(philo->do_lock);
	}
	if (finish_eating == philo->num_philo)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->done_or_die = FLAG_ON;
		pthread_mutex_unlock(philo->dead_lock);
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief check philo condition (waiter)
 * @param arg: the param was casted to t_philo struct
 * @note 1. if philo is dead or done eating, break the loop
*/
void	check_philo_condition(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
		if (check_dead(philo) == TRUE || check_done_eating(philo) == TRUE)
			break ;
}
