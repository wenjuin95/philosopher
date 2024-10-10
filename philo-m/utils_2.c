/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:40:05 by welow             #+#    #+#             */
/*   Updated: 2024/04/11 17:40:05 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief wait for the time given in milliseconds
 * @param time the time to wait
 * @return 0 if success
 * @note 1. 500microsec = 0.5ms
 * @note 2. purpose for make this function is to get the precise timing
 * @note 3. example usleep(500) is more then 0.5ms, if usleep_ms(500) is 0.5ms
 * 		    so it is more precise
*/
int	usleep_ms(long time)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time)
		usleep(500);
	return (0);
}

/**
 * @brief Get a precise current time in milliseconds
 * @return current time in milliseconds
 * @note 1. sec->milisec->microsec
 * @note 2. tv_sec is the number of seconds
 * @note 3. tv_usec is the number of microseconds
*/
long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Print the time, philo id and the message of each philo
 * @param str the message to print
 * @param philo get time_start_eat from philo struct
 * @param id the philo id
 * @note 1. current time - start time to eat = actual time
 * @note 2. if philo is done or die, do not print the message
 * @note 3. if no lock is used, the message can be printed wrong in the middle
*/
void	philo_say(char *str, t_philo *philo, int id)
{
	int	time;

	pthread_mutex_lock(philo->do_lock);
	time = get_time_ms() - philo->time_start_eat;
	if (philo_done_die(philo) == FALSE)
	{
		printf("%d %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->do_lock);
}

//assign the time and the number of philo eat to philo struct
/**
 * @brief Assign the time and the number of philo eat to philo struct
 * @param philo the philo struct
 * @param av the input arguments
 * @note 1. assign the time to die, eat, sleep and the number of philo eat
 * @note 2. if the number of philo eat is not given, assign -1
*/
void	assign_time(t_philo *philo, char **av)
{
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		philo->num_for_philo_eat = ft_atol(av[5]);
	else
		philo->num_for_philo_eat = -1;
}
