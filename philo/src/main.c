/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:17 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/13 13:57:21 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	init(t_philo_data *data);
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
	data->forks = malloc(sizeof(enum e_fork) * data->number_of_philosophers);
	if (!data->forks)
	{
		free(data->philosophers);
		return (ft_error(ERR_ALLOC));
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
	return (0);
}
