/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschulle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:31:31 by cschulle          #+#    #+#             */
/*   Updated: 2019/01/13 18:49:51 by cschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "libft/libft.h"
#include <fcntl.h>

int	get_next_line(const int fd, char **line);

#define BUFF_SIZE 3
#define FD_MAX 4864
#define MCHECK(x) if (!x) return (-1);

#define RED "\e[0;31m"
#define GRY "\e[38;5;240m"
#define YLW "\e[38;5;220m"
#define WHT "\e[0m"

#endif
