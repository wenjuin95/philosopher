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

void	philo_think(t_philo *philo)
{
	philo_say("is thinking", philo, philo->philo_id);
}

/*
*	wait for the time to sleep given
*/
void	philo_sleep(t_philo *philo)
{
	philo_say("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}

/*
*	1. philo take the right fork
*	2. check if only 1 philo, just sleep and return and unlock the right fork
*	3. if not philo take the left fork
*	4. philo start to eat and on flag eating (1 is on)
*	5. lock the meal_lock 
*		a.to get the last meal time and increment number of meal for each philo
*	6. unlock the meal_lock
* 	7. wait for next meal with time to eat given
*	8. philo is not eating (0 is off)
*	9. unlock the left and right fork
*/
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	if (philo->num_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	philo->eating = 1;
	philo_say("is eating", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->num_meal++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
