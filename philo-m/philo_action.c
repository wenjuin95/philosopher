/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:11:14 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 18:11:14 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief wait for the time to sleep given and print the message
 * @param philo the philo struct
 */
void	philo_sleep(t_philo *philo)
{
	philo_say("is sleeping", philo, philo->philo_id);
	usleep_ms(philo->time_to_sleep);
}

/**
 * @brief handle only two philo is to prevent deadlock
 * @param philo get philo forks
 * @note 1. if philo id is even, he will lock the right fork first
 * @note 2. if philo id is odd, he will lock the left fork first
*/
void handle_two_philo_fork(t_philo *philo)
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	if (philo->philo_id % 2 == 0)
	{
		l_fork = philo->right_fork;
		r_fork = philo->left_fork;
	}
	else
	{
		l_fork = philo->left_fork;
		r_fork = philo->right_fork;
	}
	(pthread_mutex_lock(l_fork), pthread_mutex_lock(r_fork));
	philo_say("has taken a fork", philo, philo->philo_id);
	philo_say("has taken a fork", philo, philo->philo_id);
}

/**
 * @brief philo take the fork and eat
 * @param philo the philo struct
 * @note 1. if philo only 1, just wait for the time to die
 * @note 2. when philo have both fork, "eating" flag is on (for let the
 * 			check_philo_condition know they are eating)
 * @note 3. after eating, increase the num_meal and update the last_meal time
 * @note 4. wait for the next time to eat and turn off the "eating" flag
 * @note 5. all the value in the do-lock is for "check_philo_condition" to check
 * @note 6. if no lock is used, the value of the variable can be in the middle
*/
void	philo_eat(t_philo *philo)
{
	if (philo->num_philo == 1)
	{
		usleep_ms(philo->time_to_die);
		return ;
	}
	if (philo->num_philo == 2)
		handle_two_philo_fork(philo);
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		philo_say("has taken a fork", philo, philo->philo_id);
		philo_say("has taken a fork", philo, philo->philo_id);
	}
	philo_say(EAT, philo, philo->philo_id);
	pthread_mutex_lock(philo->do_lock);
	philo->eating = FLAG_ON;
	philo->last_meal = get_time_ms();
	philo->num_meal++;
	philo->eating = FLAG_OFF;
	pthread_mutex_unlock(philo->do_lock);
	usleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
