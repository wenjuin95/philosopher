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

void	philo_sleep(t_philo *philo)
{
	philo_say("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep); //sleep for the time to sleep
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	if (philo->num_philo == 1)
	{
		ft_usleep(philo->time_to_die); //if there is only 1 philo, it will die
		pthread_mutex_unlock(philo->right_fork);
		return ; //return main function
	}
	pthread_mutex_lock(philo->left_fork);
	philo_say("has taken a fork", philo, philo->philo_id);
	philo->eating = 1; //1 is philo is eating
	philo_say("is eating", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time(); //get the time of the last meal
	philo->num_meal++; //increment the number of meal
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat); //sleep for the time to eat
	philo->eating = 0; //0 is philo is not eating
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
