/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:57:44 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 13:04:16 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

/*
** Prints error message and returns EXIT_FAILURE
*/
int ft_err(const char *str);

/*
** Returns integer value from str
*/
int ft_atoi(const char *str);

/*
** Returns current time in milliseconds
*/
int ft_cur_time_in_ms();

/*
** Prints "timestamp_in_ms id str"
*/
void ft_log(int id, const char *str);
#endif
