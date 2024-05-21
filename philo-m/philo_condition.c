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

//function to check if philo is dead for "check_dead"
/*
*	1. (get_time() - philo->last_meal) is the time since philo last ate
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

//check if philo is dead
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

/*
*	1. finish_eating++ :: hold the number of philo that has finished eating
*	(if finish_eating = 1 it always count only 1 philo finish eating)
*	2. finish_eating == philo->num_philo :: all philo has finished eating
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

/*
*	note:
*	1. check_dead: check is philo die
*	2. check_done_eating: check the number given to eat had done
*/
void	*check_philo_condition(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
		if (check_dead(philo) == TRUE || check_done_eating(philo) == TRUE)
			break ;
	return (NULL);
}
