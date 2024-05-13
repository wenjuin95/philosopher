/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:11:03 by welow             #+#    #+#             */
/*   Updated: 2024/05/13 13:43:53 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//this function is to delete all the mutex
void	destroy_all_mutex(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->do_lock);
	while (++i < table->philo->num_philo)
		pthread_mutex_destroy(&table->fork[i]);
}

//use atol to make sure not to overflow
long	ft_atol(const char *str)
{
	int		sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
			i++;
		}
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

//check the input only have number
int	check_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("%sMust be a number\n", RED);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
