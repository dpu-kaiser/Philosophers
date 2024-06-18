/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:55 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/18 15:28:53 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include <stdio.h>
# include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
# include <sys/time.h>
# include <pthread.h>

# define ERR_USAGE \
	"Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_philosopher_must_eat]"
# define ERR_ALLOC "Failed to allocate memory."
# define ERR_MUTEX "Failed to initialize mutex."

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
	pthread_t		tid;
	enum e_state	state;
	unsigned int	time_state_entered;
	unsigned int	times_eaten;
	unsigned int	time_last_eaten;
}					t_philosopher;

enum				e_action
{
	THINK = 0,
	SLEEP = 1,
	EAT = 2,
	DIE = 3,
	TAKE_FORK = 4,
	CONTINUE = 5
};

enum e_fork_state { TAKEN, AVAILABLE };

typedef struct s_fork
{
	enum e_fork_state state;
	pthread_mutex_t lock;
}   t_fork;

typedef struct s_philo_data
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_philosopher_must_eat;
	t_state			states[3];
	t_philosopher	*philosophers;
	t_fork		*forks;
	unsigned int	start_time;
}					t_philo_data;

typedef struct s_thread_args {
	unsigned int philo_nbr;
	t_philo_data *data;
} t_thread_args;

int					ft_error(char *msg);
unsigned int		ft_atou(const char *str);
unsigned int		get_current_time_in_ms(void);
void				philo_log(unsigned int philo_nbr, enum e_action action);
int					read_args(int argc, char *argv[], t_philo_data *data);

void				init_states(t_philo_data *data);
void				enter_state(t_philo_data *data, int philo_nbr,
						enum e_state state);
int					should_die(t_philo_data *data, int philo_nbr,
						unsigned int current_time);
int					take_forks_if_available(t_philo_data *data, int philo_nbr);

int					should_exit_thinking(int philo_nbr, void *args);
int					should_exit_eating(int philo_nbr, void *args);
int					should_exit_sleeping(int philo_nbr, void *args);


int create_pthreads(t_philo_data *data);
void join_pthreads(t_philo_data *data);

#endif
