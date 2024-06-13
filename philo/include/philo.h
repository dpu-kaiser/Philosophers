/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:55 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/13 11:52:30 by dkaiser          ###   ########.fr       */
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

enum				e_state
{
	THINKING = 0,
	EATING = 1,
	SLEEPING = 2
};

typedef struct s_state
{
	void			(*on_enter)(int, void *);
	int				(*should_exit)(int, void *);
}					t_state;

typedef struct s_philosopher
{
	// pthread_t thread;
	enum e_state	state;
	unsigned int	time_state_entered;
	unsigned int	times_eaten;
	unsigned int	time_last_eaten;
}					t_philosopher;

enum				e_action
{
	THINK = THINKING,
	SLEEP = SLEEPING,
	EAT = EATING,
	DIE,
	TAKE_FORK
};

typedef struct s_philo_data
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_philosopher_must_eat;
	t_state			states[3];
	t_philosopher	*philosophers;
	unsigned int	start_time;
}					t_philo_data;

int					ft_error(char *msg);
unsigned int		ft_atou(const char *str);
unsigned int		get_current_time_in_ms(void);
void				philo_log(unsigned int philosopher, enum e_action action);
int					read_args(int argc, char *argv[], t_philo_data *data);

void				init_states(t_philo_data *data);
void				enter_state(t_philo_data *data, int philosopher,
						enum e_state state);
int					should_die(t_philo_data *data, int philosopher,
						unsigned int current_time);

int					should_exit_thinking(int philo_nbr, void *args);
int					should_exit_eating(int philo_nbr, void *args);
int					should_exit_sleeping(int philo_nbr, void *args);

#endif
