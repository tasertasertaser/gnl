/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evjohnst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:45:35 by evjohnst          #+#    #+#             */
/*   Updated: 2019/01/12 19:35:07 by cschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FD_MAX specifies the maximum number of file descriptors get_next_line will
**	handle. Since OS X defaults to allowing users 4864 fds, do the same.
**	This value can be checked and changed with "ulimit -n [new FD_MAX]"
*/

#include "get_next_line.h"

char	*ft_strjoinfree(char *s1, const char *s2)
{
	char	*str;

	if ((s1 != NULL && s2 != NULL) && \ // checks for null arguments
	(str = ft_strjoin(s1, s2))) // joins s1 and s2, sets result at pointer str, condition false if fails
	{
		free(s1); // frees non-const pointer (was malloc'd in ??)
		return (str); //returns pointer
	}
	else
		return (NULL); // returns null if any errors
}

int		read_next_buf(char **buf_store, int fd, char *buf, char **line)
{
	int		bytes_read;
	char	*pos;

	bytes_read = read(fd, buf, BUFF_SIZE); //runs read() to get #of bytes read
	if (bytes_read == -1) // check for read() error
		return (-1);
	if ((!buf_store[fd] || buf_store[fd][0] == '\0') && bytes_read == 0) // ??
		return (0);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		pos = ft_strchr(buf, '\n');
		if (pos) // if buf contains a newline
		{
			*pos = '\0';
			*line = ft_strjoinfree(*line, buf);
			buf_store[fd] = ft_strdup(pos + 1); // store what's after \n in buf_store_fd (static)
			return (1);
		}
		*line = ft_strjoinfree(*line, buf);
		if (!pos && bytes_read < BUFF_SIZE && buf_store[fd]) // how find end of file
			free(buf_store[fd]);
		bytes_read = read(fd, buf, BUFF_SIZE);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buf_store[FD_MAX] = {NULL}; // empty array of size 4864 (max fd's UNIX can handle) to store fd (or fds)
	char		buf[BUFF_SIZE + 1]; // buffer array of size BUF_SIZE, add 1 to account for ??
	char		*pos;	// ??

	if (line == NULL || fd < 0 || fd >= FD_MAX || read(fd, buf, 0) < 0 \
		|| BUFF_SIZE <= 0 || !(*line = ft_strnew(1)))
		return (-1);
	if (buf_store[fd] && buf_store[fd][0] != '\0') // checking if anything in buf_store for that fd
	{
		*line = ft_strjoinfree(*line, buf_store[fd]);
		free(buf_store[fd]);
		if ((pos = ft_strchr(*line, '\n')))
		{
			*pos = '\0';
			buf_store[fd] = ft_strdup(pos + 1);
			return (1);
		}
	}
	return (read_next_buf(buf_store, fd, buf, line));
}
