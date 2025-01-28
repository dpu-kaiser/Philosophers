/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:15:40 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/28 13:05:31 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->owner == 0)
	{
		fork->owner = philo->id;
		ft_log(philo->id, "has taken a fork");
	}
	pthread_mutex_unlock(&fork->mutex);
}

static void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->owner = 0;
	pthread_mutex_unlock(&fork->mutex);
}

static void	eat(t_philo *philo, t_fork *left_fork, t_fork *right_fork)
{
	int	started_eating;

	started_eating = ft_cur_time_in_ms();
	ft_log(philo->id, "is eating");
	while (ft_cur_time_in_ms() < started_eating + philo->data->time_to_eat)
	{
		if (!philo->data->simulation_running)
			return ;
		if (philo_die(philo))
			return ;
		usleep(250);
	}
	philo->last_time_eaten = ft_cur_time_in_ms();
	philo->times_must_eat -= 1;
	release_fork(left_fork);
	release_fork(right_fork);
}

void	philo_eat(t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &philo->data->forks[philo->id - 1];
	right_fork = &philo->data->forks[philo->id % philo->data->nbr_of_philos];
	while (left_fork->owner != philo->id || right_fork->owner != philo->id)
	{
		if (philo->id % 2 == 0)
			take_fork(philo, right_fork);
		else if (philo->id % 2 == 1)
			usleep(250);
		take_fork(philo, left_fork);
		take_fork(philo, right_fork);
		if (!philo->data->simulation_running)
			return ;
		if (philo_die(philo))
			return ;
		if (left_fork->owner == philo->id && right_fork->owner == philo->id)
			break ;
		if (philo->id % 2 == 0)
			usleep(250);
	}
	if (philo->data->nbr_of_philos > 1)
		eat(philo, left_fork, right_fork);
}
