/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:32:17 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/18 16:30:07 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_run(void *args)
{
	t_philo_data	*data;
	unsigned int	philo_nbr;
	enum e_action	next_action;
	int				running;

	data = ((t_thread_args *)args)->data;
	philo_nbr = ((t_thread_args *)args)->philo_nbr;
	free(args);
	enter_state(data, philo_nbr, THINKING);
	running = 1;
	while (running)
	{
		next_action = data->states[data->philosophers[philo_nbr].state].should_exit(philo_nbr,
				data);
		while (next_action == CONTINUE)
		{
			next_action = data->states[data->philosophers[philo_nbr].state].should_exit(philo_nbr,
					data);
		}
		if (next_action == DIE)
		{
			philo_log(philo_nbr, DIE);
			running = 0;
		}
		else
			enter_state(data, philo_nbr, (enum e_state)next_action);
	}
	return (NULL);
}

int	create_pthreads(t_philo_data *data)
{
	unsigned int	i;
	int				error;
	t_thread_args	*args;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		args = malloc(sizeof(t_thread_args));
		if (!args)
			return (ft_error(ERR_ALLOC));
		args->data = data;
		args->philo_nbr = i;
		error = pthread_create(&data->philosophers[i].tid, NULL, &thread_run,
				args);
		if (error)
			return (error); // Add message
		i++;
	}
	return (0);
}

void	join_pthreads(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].tid, NULL);
		i++;
	}
}
