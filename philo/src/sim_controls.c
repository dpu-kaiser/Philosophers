/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:32:28 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/28 13:45:20 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_running(t_phdata *data)
{
	int	result;

	pthread_mutex_lock(&data->sr_mutex);
	result = data->simulation_running;
	pthread_mutex_unlock(&data->sr_mutex);
	return (result);
}

void	stop_simulation(t_phdata *data)
{
	pthread_mutex_lock(&data->sr_mutex);
	data->simulation_running = 0;
	pthread_mutex_unlock(&data->sr_mutex);
}
