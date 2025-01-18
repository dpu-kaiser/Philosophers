/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 12:26:53 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_philo *philo)
{
    t_fork *left_fork;
    t_fork *right_fork;

    left_fork = &philo->data->forks[philo->id];
    right_fork = &philo->data->forks[(philo->id + 1) % philo->data->nbr_of_philos];
    if (left_fork->available && right_fork->available)
    {
        pthread_mutex_lock(&left_fork->mutex);
        pthread_mutex_lock(&right_fork->mutex);
        left_fork->available = 0;
        right_fork->available = 0;
        printf("Philo %d is eating\n", philo->id);
        usleep(1000000);
        left_fork->available = 1;
        right_fork->available = 1;
        pthread_mutex_unlock(&left_fork->mutex);
        pthread_mutex_unlock(&right_fork->mutex);
    }
   return (EXIT_SUCCESS);
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
        *result = eat(philo);
        printf("Philo %d is sleeping\n", philo->id);
        usleep(1000000);
        //think
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
