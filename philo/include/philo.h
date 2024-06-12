/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:55 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/12 12:58:06 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"

# define ERR_USAGE \
	"Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_philosopher_must_eat]"

typedef struct s_philo_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_philosopher_must_eat;
}		t_philo_data;

int		ft_error(char *msg);
int		ft_atoi(const char *str);
int		read_args(int argc, char *argv[], t_philo_data *data);

#endif
