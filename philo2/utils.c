/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:11:03 by welow             #+#    #+#             */
/*   Updated: 2024/04/12 16:12:17 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_table *table, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	while (++i < table->philo->num_philo)
		pthread_mutex_destroy(&fork[i]);
}

//for error output
void	error_output(const char *str)
{
	printf("%s%s", RED, str);
	exit(EXIT_FAILURE);
}

//use atol to make sure not to overflow
int	ft_atol(const char *str)
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
	if (res >= INT_MAX)
		error_output("too big number\n");
	return (sign * res);
}

void	check_digit(char **av)
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
				error_output("must be a number\n");
			j++;
		}
		i++;
	}
}
