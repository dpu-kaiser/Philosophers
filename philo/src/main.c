/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:13:30 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/28 14:25:27 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	load_data(t_phdata *data, int argc, char *argv[])
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->times_must_eat = ft_atoi(argv[5]);
		if (data->times_must_eat < 1)
			return (ft_err("times_must_eat can't be negative or zero"));
	}
	else
		data->times_must_eat = -1;
	if (data->nbr_of_philos <= 0)
		return (ft_err("Must have at least one philosopher"));
	if (data->time_to_die < 0)
		return (ft_err("ttd can't be negative"));
	if (data->time_to_eat < 0)
		return (ft_err("tte can't be negative"));
	if (data->time_to_sleep < 0)
		return (ft_err("tts can't be negative"));
	data->philos_must_eat = data->nbr_of_philos;
	return (EXIT_SUCCESS);
}

void	free_data(t_phdata *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->pme_mutex);
	pthread_mutex_destroy(&data->sr_mutex);
}

int	main(int argc, char *argv[])
{
	t_phdata	data;
	t_philo		*philos;
	int			result;

	if (argc != 5 && argc != 6)
		return (ft_err(ERR_USAGE));
	result = load_data(&data, argc, argv);
	if (result != EXIT_SUCCESS)
		return (result);
	result = init(&philos, &data);
	if (result != EXIT_SUCCESS)
		return (result);
	result = run_simulation(data.nbr_of_philos, philos, &data);
	free(philos);
	free_data(&data);
	return (result);
}
