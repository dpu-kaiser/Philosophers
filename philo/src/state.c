/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:59:03 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/13 12:15:12 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_states(t_philo_data *data)
{
	data->states[THINKING] = (t_state){NULL, &should_exit_thinking};
	data->states[EATING] = (t_state){NULL, &should_exit_eating};
	data->states[SLEEPING] = (t_state){NULL, &should_exit_sleeping};
}

void	enter_state(t_philo_data *data, int philo_nbr, enum e_state state)
{
	data->philosophers[philo_nbr].time_state_entered = get_current_time_in_ms();
	data->philosophers[philo_nbr].state = state;
	philo_log(philo_nbr, (enum e_action)state);
}

int	should_die(t_philo_data *data, int philo_nbr, unsigned int current_time)
{
	current_time = get_current_time_in_ms();
	if (data->philosophers[philo_nbr].times_eaten == 0 && data->start_time
		+ data->time_to_die < current_time)
		return (1);
	else if (data->philosophers[philo_nbr].time_last_eaten
		+ data->time_to_die < current_time)
		return (1);
	else
		return (0);
}
