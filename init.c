/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:19:17 by welow             #+#    #+#             */
/*   Updated: 2024/04/08 15:24:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//assign mutex for each of the philo
/*
*	1. check if philo is weither done or die
*	2. philo start taking the fork
* 	3. check if philo is weither done or die
*		a. if done or die, unlock the fork
*	4. philo start eating
*	5. check if philo is weither done or die
*	6. philo start sleeping
*	7. check if philo is weither done or die
*	8. philo start thinking
*/
void	philo_move(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (philos->table->done_or_die == 0)
	{
		if (philo_finish(philos) == 1)
			return (NULL);
		philo_fork(philos);
		if (philo_finish(philos) == 1)
		{
			pthread_mutex_unlock(philos->table->left_fork);
			pthread_mutex_unlock(philos->table->right_fork);
			return (NULL);
		}
		philo_eating(philos);
		if (philo_finish(philos) == 1)
			return (NULL);
		philo_sleeping(philos);
		if (philo_finish(philos) == 1)
			return (NULL);
		philo_thinking(philos);
	}
	return (NULL);
}

//assign time for each of the philo
//create a thread for each of the philo
void	start_table(t_table *table)
{
	int	i;

	i = 0;
	table->time_for_start_table = get_time();
	while (i < table->num_philo)
	{
		pthread_create(&table->philo[i].thread_id, NULL, &philo_move,
			&table->philo[i]);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}
