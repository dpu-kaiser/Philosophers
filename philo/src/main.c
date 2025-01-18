/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:13:30 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 11:36:33 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int load_data(t_phdata *data, int argc, char *argv[])
{
    data->nbr_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->times_must_eat = ft_atoi(argv[2]);
    else
        data->times_must_eat = -1;
    if (data->nbr_of_philos <= 0)
        return (ft_err("Must have at least one philosopher"));
    if (data->time_to_die < 0)
        return (ft_err("ttd can't be negative"));
    if (data->time_to_eat < 0)
        return (ft_err("tte can't be negative"));
    if (data->time_to_sleep < 0)
        return (ft_err("tts can't be negative"));
    return (EXIT_SUCCESS);
}

int init(t_philo **philos, t_phdata *data)
{
    int i;
    int result;

    *philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philos);
    if (*philos == NULL)
        return (ft_err(ERR_MALLOC));
    data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_of_philos);
    if (data->forks == NULL)
    {
        free(*philos);
        return (ft_err(ERR_MALLOC));
    }
    i = 0;
    while (i < data->nbr_of_philos)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].is_alive = 1;
        (*philos)[i].times_eaten = 0;
        (*philos)[i].data = data;
        data->forks[i].available = 1;
        result = pthread_mutex_init(&(data->forks[i].mutex), NULL);
        if (result != 0)
            return (result);
        i++;
    }
    return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    t_phdata data;
    t_philo *philos;
    int result;

    if (argc != 5 && argc != 6)
        return(ft_err(ERR_USAGE));
    result = load_data(&data, argc, argv);
    if (result != EXIT_SUCCESS)
        return (result);
    result = init(&philos, &data);
    if (result != EXIT_SUCCESS)
        return (result);
    result = run_simulation(data.nbr_of_philos, philos);
    free(philos);
    free(data.forks);
    return (result);
}
