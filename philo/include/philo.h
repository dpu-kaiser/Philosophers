/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:55 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/12 14:45:38 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include <stdio.h>
# include <sys/_types/_timeval.h>
# include <sys/time.h>

# define ERR_USAGE \
	"Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_philosopher_must_eat]"

typedef struct s_philo_data
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_philosopher_must_eat;
}					t_philo_data;

enum				e_philo_state
{
	THINKING,
	SLEEPING,
	EATING
};

typedef struct s_state
{
	void			(*on_enter)(int, t_philo_data *);
	void			(*on_exit)(int, t_philo_data *);
	int				(*exit_if)(int, t_philo_data *);
	unsigned int	time_entered;
}					t_state;

enum				e_action
{
	THINK,
	SLEEP,
	EAT,
	DIE,
	TAKE_FORK
};

int					ft_error(char *msg);
unsigned int		ft_atou(const char *str);
unsigned int		get_current_time_in_ms(void);
void				philo_log(unsigned int philosopher, enum e_action action);
int					read_args(int argc, char *argv[], t_philo_data *data);

#endif
