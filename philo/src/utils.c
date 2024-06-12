/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:06:00 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/12 13:52:39 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, msg, len);
	write(2, "\n", 1);
	return (1);
}

unsigned int	ft_atou(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	return (result);
}

void	philo_log(unsigned int philosopher, enum e_action action)
{
	struct timeval	time;
	unsigned int	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (action == TAKE_FORK)
		printf("%u %u has taken a fork\n", time_in_ms, philosopher);
	else if (action == EAT)
		printf("%u %u is eating\n", time_in_ms, philosopher);
	else if (action == THINK)
		printf("%u %u is thinking\n", time_in_ms, philosopher);
	else if (action == SLEEP)
		printf("%u %u is sleeping\n", time_in_ms, philosopher);
	else if (action == DIE)
		printf("%u %u died\n", time_in_ms, philosopher);
}
