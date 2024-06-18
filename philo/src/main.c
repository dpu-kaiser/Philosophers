/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:17 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/18 16:29:59 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static int	init(t_philo_data *data);
static int	init_forks(t_philo_data *data);
static void	cleanup(t_philo_data *data);
static int	start_simulation(t_philo_data *data);

int	main(int argc, char *argv[])
{
	t_philo_data	data;
	int				result;

	if (argc != 5 && argc != 6)
		return (ft_error(ERR_USAGE));
	if (read_args(argc, argv, &data))
		return (ft_error(ERR_USAGE));
	result = init(&data);
	if (result)
		return (result);
	result = start_simulation(&data);
	cleanup(&data);
	return (result);
}

static int	init(t_philo_data *data)
{
	data->philosophers = malloc(sizeof(t_philosopher)
			* data->number_of_philosophers);
	if (!data->philosophers)
		return (ft_error(ERR_ALLOC));
	data->philosophers[0].times_eaten = 0;
	data->philosophers[1].times_eaten = 0;
	data->philosophers[2].times_eaten = 0;
	data->forks = malloc(sizeof(t_fork) * data->number_of_philosophers);
	if (!data->forks)
	{
		free(data->philosophers);
		return (ft_error(ERR_ALLOC));
	}
	init_states(data);
	if (init_forks(data))
		return (ft_error(ERR_MUTEX));
	return (0);
}

static int	init_forks(t_philo_data *data)
{
	unsigned int	i;
	int				error;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->forks[i].state = AVAILABLE;
		error = pthread_mutex_init(&data->forks[i].lock, NULL);
		if (error)
		{
			// FREE
			return (error);
		}
		i++;
	}
	return (0);
}

static void	cleanup(t_philo_data *data)
{
	free(data->philosophers);
	free(data->forks);
}

static int	start_simulation(t_philo_data *data)
{
	int	result;

	data->start_time = get_current_time_in_ms();
	printf("start_time: %u\nnumber_of_philosophers: %u\ntime_to_die:
		%u\ntime_to_eat: %u\ntime_to_sleep: %u\n", data->start_time,
		data->number_of_philosophers, data->time_to_die, data->time_to_eat,
		data->time_to_sleep);
	result = create_pthreads(data);
	if (result)
		return (result);
	join_pthreads(data);
	return (result);
}
