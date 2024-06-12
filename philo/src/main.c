/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:56:17 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/12 12:56:39 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_data	data;

	if (argc != 5 && argc != 6)
		return (ft_error(ERR_USAGE));
	if (read_args(argc, argv, &data))
		return (ft_error(ERR_USAGE));
}
