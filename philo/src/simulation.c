/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 12:49:42 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eat(t_philo *philo)
{
    t_fork *left_fork;
    t_fork *right_fork;

    left_fork = &philo->data->forks[philo->id];
    right_fork = &philo->data->forks[(philo->id + 1) % philo->data->nbr_of_philos];
    while (!left_fork->available || !right_fork->available)
    {
        // die if waiting too long
    }
    pthread_mutex_lock(&left_fork->mutex);
    pthread_mutex_lock(&right_fork->mutex);
    left_fork->available = 0;
    ft_log(philo->id, "has taken a fork");
    right_fork->available = 0;
    ft_log(philo->id, "has taken a fork");
    ft_log(philo->id, "is eating");
    usleep(1000000);
    left_fork->available = 1;
    right_fork->available = 1;
    pthread_mutex_unlock(&left_fork->mutex);
    pthread_mutex_unlock(&right_fork->mutex);
}

void philo_sleep(t_philo *philo)
{
    ft_log(philo->id, "is sleeping");
    usleep(1000000);
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
        philo_sleep(philo);
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
