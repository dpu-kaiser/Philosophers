/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:13:30 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/17 11:53:53 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_err(char *str)
{
    printf("\e[31m[ERROR] %s\e[0m\n", str);
    return (EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    t_phdata data;
    int result;

    if (argc != 5 && argc != 6)
        return(ft_err(ERR_USAGE));
    result = load_data(&data, argc, argv);
    if (result != EXIT_SUCCESS)
        return (result);
    return (EXIT_SUCCESS);
}
