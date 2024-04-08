/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:38:02 by welow             #+#    #+#             */
/*   Updated: 2024/04/08 16:10:22 by welow            ###   ########.fr       */
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
*	  a. if left fork not lock, unlock the right fork and return 1(means error)
*	  b. if left fork lock and if philo not finish, said "has taken a fork"
*	5. if philo is odd
*	  a. if left fork not lock, unlock the right fork and return 1(means error)
*	  b. if left fork lock and if philo not finish, said "has taken a fork"
*/
int	philo_fork(t_philo *philos)
{
	if (philos->philo_id % 2 == 0)
		pthread_mutex_lock(philos->right_fork);
	else
		pthread_mutex_lock(philos->left_fork);
	if (philosopher_finish(philos) == 0)
		philo_say(philos, "has taken a fork");
	if (philos->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philos->left_fork) != 0)
			return (pthread_mutex_unlock(philos->right_fork), 1);
		if (philosopher_finish(philos) == 0)
			philo_say(philos, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philos->left_fork) != 0)
			return (pthread_mutex_unlock(philos->right_fork));
		if (philosopher_finish(philos) == 0)
			philo_say(philos, "has taken a fork");
	}
	return (0);
}
