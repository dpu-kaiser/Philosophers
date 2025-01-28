/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:12:57 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/28 14:28:58 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static void	init_philo(t_philo *philo, t_phdata *data, int id);
static int	init_philos(t_philo **philos, t_phdata *data);

int	init(t_philo **philos, t_phdata *data)
{
	int	result;

	*philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (*philos == NULL)
		return (ft_err(ERR_MALLOC));
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_of_philos);
	if (data->forks == NULL)
	{
		free(*philos);
		return (ft_err(ERR_MALLOC));
	}
	result = pthread_mutex_init(&(data->pme_mutex), NULL);
	if (result != 0)
	{
		free(*philos);
		free_data(data);
		return (result);
	}
	result = pthread_mutex_init(&data->sr_mutex, NULL);
	if (result != 0)
	{
		free(*philos);
		free_data(data);
		return (result);
	}
	result = init_philos(philos, data);
	return (result);
}

static int	init_philos(t_philo **philos, t_phdata *data)
{
	int	i;
	int	result;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		init_philo(&(*philos)[i], data, i + 1);
		data->forks[i].owner = 0;
		result = pthread_mutex_init(&(data->forks[i].mutex), NULL);
		if (result != 0)
		{
			free(*philos);
			free(data->forks);
			return (result);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	init_philo(t_philo *philo, t_phdata *data, int id)
{
	philo->id = id;
	philo->is_alive = 1;
	philo->times_must_eat = data->times_must_eat;
	philo->data = data;
	philo->last_time_eaten = ft_cur_time_in_ms();
}
