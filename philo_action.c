/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:38:02 by welow             #+#    #+#             */
/*   Updated: 2024/04/10 18:24:12 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//purpose of this function is to check if the philo is done or die
int	philo_finish(t_philo *philos)
{
	pthread_mutex_lock(&philos->table->mutex);
	if (philos->table->done_or_die == 1)
	{
		pthread_mutex_unlock(&philos->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->table->mutex);
	return (0);
}

/*
*	1. if philo is even, take the right fork first
*	2. if philo is odd, take the left fork first
*	3. if philo is not finish, said "has taken a fork"
*	4. if philo is even
*	  a. if philo can't lock the left fork, unlock the right fork 
*		 that philo already lock
*	  b. if philo not finish, then said "has taken a fork"
*	5. if philo is odd
*	  a. if he can't lock the right fork, unlock the left fork 
*		 that philo already lock
*	  b. if philo not finish, said "has taken a fork"
*/
//note: return(xxxx, 1): return the xxxx then 1
int	philo_fork(t_philo *philos)
{
	if (philos->philo_id % 2 == 0)
		pthread_mutex_lock(philos->right_fork);
	else
		pthread_mutex_lock(philos->left_fork);
	if (philo_finish(philos) == 1)
		philo_say(philos, "has taken a fork");
	if (philos->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philos->left_fork) != 0)
			return (pthread_mutex_unlock(philos->right_fork), 1);
		if (philo_finish(philos) == 0)
			philo_say(philos, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philos->left_fork) != 0)
			return (pthread_mutex_unlock(philos->right_fork), 1);
		if (philo_finish(philos) == 0)
			philo_say(philos, "has taken a fork");
	}
	return (0);
}

/*
*	1. if philo is not finish, said "is eating"
*	2. last meal is the time now - time for start table
*	3. time to die is last meal + time to die
*	4. usleep for time to eat
*	5. if philo of number of meal not done, increment the number of meal
*/
//lock and unlock is to check the current philo
void	philo_eating(t_philo *philos)
{
	philo_say(philos, "is eating");
	pthread_mutex_lock(&philos->table->mutex);
	philos->last_meal = get_time() - philos->table->time_for_start_table;
	philos->time_to_die = philos->last_meal + philos->table->time_to_die;
	pthread_mutex_unlock(&philos->table->mutex);
	ft_usleep(philos->table->time_to_eat, philos);
	pthread_mutex_lock(&philos->table->mutex);
	if (philos->num_meal != -1)
		philos->num_meal++;
	pthread_mutex_unlock(&philos->table->mutex);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

//if philo not finish, said "is sleeping"
void	philo_sleeping(t_philo *philos)
{
	philo_say(philos, "is sleeping");
	ft_usleep(philos->table->time_to_sleep, philos);
}

//if philo not finish, said "is thinking"
void	philo_thinking(t_philo *philos)
{
	philo_say(philos, "is thinking");
}
