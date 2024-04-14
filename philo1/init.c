/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:19:17 by welow             #+#    #+#             */
/*   Updated: 2024/04/10 23:27:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meal(t_philo *philos)
{
	if (get_time() - philos->table->time_for_start_table > philos->time_to_die)
	{
		philos->table->done_or_die = 1;
		printf("%d %d died\n", get_time()
			- philos->table->time_for_start_table, philos->philo_id);
		return (0);
	}
	else
		return (1);
}

//function is to check if each of philo is done or die
/*
*	1. get_time() - table->philo[i].table->time_for_start_table is to get the
*      philo last time to eat
*	2. if the time > time to die, the philo done or die flag on
*	3. print the time and the philo id and philo died
*/
// int	philo_die(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->num_philo)
// 	{
// 		if (get_time() - table->philo[i].table->time_for_start_table
// 			> table->philo[i].time_to_die)
// 		{
// 			table->philo[i].table->done_or_die = 1;
// 			printf("%d %d died\n",
// 				get_time() - table->philo[i].table->time_for_start_table,
// 				table->philo[i].philo_id);
// 			return (0);
// 		}
// 		else
// 			return (1);
// 		i++;
// 	}
// 	return (1);
// }
int	philo_die(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (check_meal(&table->philo[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}


//function is to check if the philo is done or die
/*
*	usleep is to make sure the philo is not checking too fast
*/
// void	*check_philo_is_die(void *arg)
// {
// 	t_table	*table;

// 	table = (t_table *)arg;
// 	int		i;

// 	i = 1;
// 	while (i != 0)
// 	{
// 		pthread_mutex_lock(&table->mutex);
// 		if (philo_die(table) == 0)
// 		{
// 			usleep(100);
// 			pthread_mutex_unlock(&table->mutex);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&table->mutex);
// 		usleep(200);
// 	}
// 	return (NULL);
// }
void	*check_philo_is_die(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->mutex);
		if (philo_die(table) == 0)
		{
			usleep(100);
			return (pthread_mutex_unlock(&table->mutex), NULL);
		}
		pthread_mutex_unlock(&table->mutex);
		usleep(200);
	}
}

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
// void	*philo_move(void *arg)
// {
// 	t_philo	*philos;

// 	philos = (t_philo *)arg;
// 	while (philos->table->done_or_die == 0)
// 	{
// 		if (philo_finish(philos) == 1)
// 			return (NULL);
// 		philo_fork(philos);
// 		if (philo_finish(philos) == 1)
// 		{
// 			pthread_mutex_unlock(philos->left_fork);
// 			pthread_mutex_unlock(philos->right_fork);
// 			return (NULL);
// 		}
// 		philo_eating(philos);
// 		if (philo_finish(philos) == 1)
// 			return (NULL);
// 		philo_sleeping(philos);
// 		if (philo_finish(philos) == 1)
// 			return (NULL);
// 		philo_thinking(philos);
// 	}
// 	return (NULL);
// }
void	*philo_move(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (philos->table->done_or_die == 0)
	{
		if (philo_finish(philos) == 1)
			return (0);
		philo_fork(philos);
		if (philo_finish(philos) == 1)
		{
			pthread_mutex_unlock(philos->left_fork);
			pthread_mutex_unlock(philos->right_fork);
			return (0);
		}
		philo_eating(philos);
		if (philo_finish(philos) == 1)
			return (0);
		philo_sleeping(philos);
		if (philo_finish(philos) == 1)
			return (0);
		philo_thinking(philos);
	}
	return (0);
}

//get_time: is to get the start time of the table
//create a thread for each of the philo
// void	start_table(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	table->time_for_start_table = get_time();
// 	while (i < table->num_philo)
// 	{
// 		pthread_create(&table->philo[i].thread_id, NULL, &philo_move,
// 			&table->philo[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < table->num_philo)
// 	{
// 		pthread_join(table->philo[i].thread_id, NULL);
// 		i++;
// 	}
// 	check_philo_is_die(table);
// 	join_thread(table);
// }
void	start_table(t_table *table)
{
	int	i;

	i = 0;
	table->time_for_start_table = get_time();
	while (i < table->num_philo)
	{
		pthread_create(&table->philo[i].thread_id, NULL, &philo_move,
			(void *)&table->philo[i]);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}