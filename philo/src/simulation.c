/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 17:02:27 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_die(t_philo *philo)
{
    if (ft_cur_time_in_ms() > philo->last_time_eaten + philo->data->time_to_die)
    {
            philo->is_alive = 0;
            ft_log(philo->id, "has died");
            philo->data->simulation_running = 0;
            return (1);
    }
    return (0);
}

void philo_eat(t_philo *philo)
{
    t_fork *left_fork;
    t_fork *right_fork;
    int started_eating;
    int tte;

    left_fork = &philo->data->forks[philo->id - 1];
    right_fork = &philo->data->forks[philo->id % philo->data->nbr_of_philos];
    while (!left_fork->available || !right_fork->available)
    {
        if (!philo->data->simulation_running)
            return;
        if (philo_die(philo))
            return ;
        usleep(1000);
    }
    pthread_mutex_lock(&left_fork->mutex);
    pthread_mutex_lock(&right_fork->mutex);
    if (philo->data->simulation_running)
    {

        left_fork->available = 0;
        ft_log(philo->id, "has taken a fork");
        right_fork->available = 0;
        ft_log(philo->id, "has taken a fork");
        started_eating = ft_cur_time_in_ms();
        tte = philo->data->time_to_eat;
        philo->last_time_eaten = started_eating;
        philo->times_must_eat -= 1;
        ft_log(philo->id, "is eating");
        while (ft_cur_time_in_ms() < started_eating + tte)
        {
            if (philo_die(philo))
                return;
            usleep(1000);
        }
        left_fork->available = 1;
        right_fork->available = 1;
    }
    pthread_mutex_unlock(&left_fork->mutex);
    pthread_mutex_unlock(&right_fork->mutex);
}

void philo_sleep(t_philo *philo)
{
    int started_sleeping;
    int tts;

    started_sleeping = ft_cur_time_in_ms();
    tts = philo->data->time_to_sleep;
    ft_log(philo->id, "is sleeping");
    while (ft_cur_time_in_ms() < started_sleeping + tts)
    {
        if (philo_die(philo))
            return;
        usleep(1000);
    }
}

void philo_think(t_philo *philo)
{
    ft_log(philo->id, "is thinking");
}

int *process_philo(void *arg)
{
    t_philo *philo;
    int *result;

    result = malloc(sizeof(int));
    if (result == NULL)
        return (NULL);
    philo = (t_philo *)arg;
    *result = EXIT_SUCCESS;
    while (philo->data->simulation_running)
    {
        philo_eat(philo);
        if (philo->times_must_eat == 0)
        {
            pthread_mutex_lock(&philo->data->pme_mutex);
            philo->data->philos_must_eat -= 1;
            if (philo->data->philos_must_eat <= 0)
                philo->data->simulation_running = 0;
            pthread_mutex_unlock(&philo->data->pme_mutex);
        }
        if (!philo->data->simulation_running)
            break;
        philo_sleep(philo);
        if (!philo->data->simulation_running)
            break;
        philo_think(philo);
    }
    return (result);
}

int run_simulation(int nbr_of_philos, t_philo *philos)
{
    int i;
    int result;
    void *retval;

    i = 0;
    result = EXIT_SUCCESS;
    while (i < nbr_of_philos)
    {
        result = pthread_create(&(philos[i].thread), NULL, (void*) process_philo, &philos[i]);
        if (result != 0)
            break;
        i++;
    }
    while (i--)
    {
        pthread_join(philos[i].thread, &retval);
        if (retval == NULL)
            result = ft_err(ERR_MALLOC);
        else if (*(int *)retval != EXIT_SUCCESS)
        {
            result = *(int *)retval;
            free(retval);
        }
    }
    return (result);
}
