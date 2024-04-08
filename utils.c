/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:11:03 by welow             #+#    #+#             */
/*   Updated: 2024/04/08 16:14:28 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//for error output
void	error_output(const char *str)
{
	printf("%s%s", RED, str);
	exit(EXIT_FAILURE);
}

//purpose is to print if the philo is done or die
void	philo_say(t_philo *philos, const char *str)
{
	if (philo_finish(philos) == 0)
	{
		pthread_mutex_lock(&philos->table->mutex);
		printf("%d %d %s\n", (get_time() - philos->table->time_for_start_table),
			philos->philo_id, str);
	}
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
