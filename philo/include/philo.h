/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:23:19 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/28 14:26:14 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_USAGE "Usage: <nbr_of_philos> <ttd> <tte> <tts> [times_must_eat]"
# define ERR_MALLOC "Memory allocation failed"

typedef struct s_fork
{
	int				owner;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_phdata
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philos_must_eat;
	pthread_mutex_t	pme_mutex;
	int				simulation_running;
	pthread_mutex_t	sr_mutex;
	t_fork			*forks;
}					t_phdata;

typedef struct s_philo
{
	int				id;
	int				last_time_eaten;
	int				times_must_eat;
	int				is_alive;
	pthread_t		thread;
	t_phdata		*data;
}					t_philo;

int					init(t_philo **philos, t_phdata *data);
void				free_data(t_phdata *data);
int					run_simulation(int nbr_of_philos, t_philo *philos,
						t_phdata *data);
int					philo_die(t_philo *philo);
void				philo_eat(t_philo *philo);

int					is_simulation_running(t_phdata *data);
void				stop_simulation(t_phdata *data);

/*
** Prints error message and returns EXIT_FAILURE
*/
int					ft_err(const char *str);

/*
** Returns integer value from str
*/
int					ft_atoi(const char *str);

/*
** Returns current time in milliseconds
*/
int					ft_cur_time_in_ms(void);

/*
** Prints "timestamp_in_ms philo->id str"
*/
void				ft_log(t_philo *philo, const char *str);

#endif
