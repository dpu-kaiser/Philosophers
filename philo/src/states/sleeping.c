/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:09:43 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/13 14:14:49 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_exit_sleeping(int philo_nbr, void *data)
{
	t_philo_data	*d;
	unsigned int	current_time;

	d = (t_philo_data *)data;
	current_time = get_current_time_in_ms();
	if (should_die(d, philo_nbr, current_time))
		return (DIE);
	else if (d->philosophers[philo_nbr].time_state_entered
		+ d->time_to_sleep < current_time)
		return (THINK);
	return (CONTINUE);
}
