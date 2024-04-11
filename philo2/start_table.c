/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:23:25 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 17:23:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check if philo is dead or done eating
int	philo_done_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->die == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_move(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0) //is even
		ft_usleep(1);
	while (philo_done_die(philo) == 0)//0 is false
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_table(t_table *table, pthread_mutex_t *fork)
{
	int	i;
	pthread_t	check_philo;

	if (pthread_create(&check_philo, NULL, &check_philo_condition, table->philo) != 0)
		destroy_all_mutex(table, fork);
	i = -1;
	while (++i < table->philo->num_philo) //philo[0]
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_move,
				&table->philo[i]) != 0)
			destroy_all_mutex(table, fork);
	}
	if (pthread_join(check_philo, NULL) != 0)
		destroy_all_mutex(table, fork);
	i = -1;
	while (++i < table->philo->num_philo) //philo[0]
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			destroy_all_mutex(table, fork);
	}
	return (0);
}
