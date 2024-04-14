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

//(get_time() - philo->last_meal) is the time since philo last ate
//philo->eating == 0 is the philo is not eating
int	philo_die(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_time() - philo->last_meal) >= time_to_die
		&& philo->eating == FLAG_OFF)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

//check if philo is dead
// 1 is true
int	check_dead(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_philo)
	{
		if (philo_die(&philo[i], philo[i].time_to_die) == 1)
		{
			philo_say("died", &philo[i], philo[i].philo_id);
			pthread_mutex_lock(philo->dead_lock);
			*philo->done_or_die = FLAG_ON;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
	}
	return (0);
}

/*
*	1. check if assign number of meal for philo if not return 0
*	2. finish_eating++ is to hold the number of philo that has finished eating
*		a. if finish_eating = 1 it always count only 1 philo finish eating
*	3. if finish_eating == philo->num_philo then all philo has finished eating
*/
int	check_done_eating(t_philo *philo)
{
	int	i;
	int	finish_eating;

	i = -1;
	finish_eating = 0;
	if (philo->num_for_philo_eat == -1)
		return (0);
	while (++i < philo->num_philo)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo[i].num_meal >= philo[i].num_for_philo_eat)
			finish_eating++;
		pthread_mutex_unlock(philo->meal_lock);
	}
	if (finish_eating == philo->num_philo)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->done_or_die = FLAG_ON;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

//check if philo is dead or done eating
void	*check_philo_condition(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (check_dead(philo) == 1 || check_done_eating(philo) == 1)
			break ;
	return (NULL);
}
