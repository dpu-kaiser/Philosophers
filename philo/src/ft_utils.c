/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:57:11 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 13:04:08 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int ft_err(const char *str)
{
    printf("\e[31m[ERROR] %s\e[0m\n", str);
    return (EXIT_FAILURE);
}

int ft_cur_time_in_ms()
{
	int time_in_ms;
	struct timeval t;

	gettimeofday(&t, NULL);
	time_in_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_in_ms);
}

void ft_log(int id, const char *str)
{
	printf("%u %d %s\n", ft_cur_time_in_ms(), id, str);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	posneg;

	posneg = 1;
	result = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		posneg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	return (result * posneg);
}
