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

//	wait for the time to sleep given
void	philo_sleep(t_philo *philo)
{
	philo_say("is sleeping", philo, philo->philo_id);
	usleep_ms(philo->time_to_sleep);
}

/*
*	1. philo take the right fork 
*		check if only 1 philo then just put down right fork
*	2. philo take the left fork
*	3. philo start to eat and on flag on
*		(for the condition to check if philo is eating)
*	4. num_meal and the last_meal is for the condition
*		a.num_meal :: get the total ofeach philo eat
*		b.last_meal :: get the last meal time
*	5. ft_usleep(philo->time_to_eat) :: wait for the next time to eat
*	6. turn off the flag means philo is not eating
*/
void	philo_eat(t_philo *philo)
{
	if (philo->num_philo == 1)
	{
		usleep_ms(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	pthread_mutex_lock(philo->left_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	philo->eating = FLAG_ON;
	philo_say(EAT, philo, philo->philo_id);
	pthread_mutex_lock(philo->do_lock);
	philo->last_meal = get_time_ms();
	philo->num_meal++;
	pthread_mutex_unlock(philo->do_lock);
	usleep_ms(philo->time_to_eat);
	philo->eating = FLAG_OFF;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
