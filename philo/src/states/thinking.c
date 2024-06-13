/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:53:36 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/13 14:14:30 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: Add logic for exiting and not just dying.
int	should_exit_thinking(int philo_nbr, void *data)
{
	t_philo_data	*d;
	unsigned int	current_time;

	d = (t_philo_data *)data;
	current_time = get_current_time_in_ms();
	if (should_die(d, philo_nbr, current_time))
		return (DIE);
	if (take_forks_if_available(d, philo_nbr))
		return (EAT);
	return (CONTINUE);
}
