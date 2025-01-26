/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/26 12:43:53 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_die(t_philo *philo)
{
	if (ft_cur_time_in_ms() > philo->last_time_eaten + philo->data->time_to_die)
	{
		philo->is_alive = 0;
		ft_log(philo->id, "has died");
		philo->data->simulation_running = 0;
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	int	started_sleeping;
	int	tts;

	started_sleeping = ft_cur_time_in_ms();
	tts = philo->data->time_to_sleep;
	ft_log(philo->id, "is sleeping");
	while (ft_cur_time_in_ms() < started_sleeping + tts)
	{
		if (philo_die(philo))
			return ;
		usleep(1000);
	}
}

void	process_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->simulation_running)
	{
		philo_eat(philo);
		if (philo->times_must_eat == 0)
		{
			pthread_mutex_lock(&philo->data->pme_mutex);
			philo->data->philos_must_eat -= 1;
			pthread_mutex_unlock(&philo->data->pme_mutex);
		}
		if (!philo->data->simulation_running)
			break ;
		if (philo->data->nbr_of_philos < 2)
		{
			if (philo_die(philo))
				break ;
			continue ;
		}
		philo_sleep(philo);
		if (!philo->data->simulation_running)
			break ;
		ft_log(philo->id, "is thinking");
	}
}

int	run_simulation(int nbr_of_philos, t_philo *philos, t_phdata *data)
{
	int	i;
	int	result;

	i = 0;
	result = EXIT_SUCCESS;
	while (i < nbr_of_philos)
	{
		result = pthread_create(&(philos[i].thread), NULL,
				(void *)process_philo, &philos[i]);
		if (result != 0)
			break ;
		i++;
	}
	while (data->simulation_running)
	{
		if (data->philos_must_eat <= 0)
			data->simulation_running = 0;
	}
	while (i--)
	{
		pthread_join(philos[i].thread, NULL);
	}
	return (result);
}
