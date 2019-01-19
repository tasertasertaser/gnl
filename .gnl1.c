/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschulle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:13:59 by cschulle          #+#    #+#             */
/*   Updated: 2019/01/16 14:47:06 by cschulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * WHAT THIS DOES
**
** 1. takes pointer-to-pointer (**line) and file descriptor (fd) as argument
** 2. reads BUFF_SIZE characters into a buffer
** 3. adds contents of buffer to string at **line pointer and continues reading until a '\n' is found
** 		• given **line now points at a single line of the given file
** 4. stores any remaining buf-read characters in a static array for next function call
** 5. return value (int) is just a flag for whether operation was completed successfully
**		•  1 = line was read
**		•  0 = file has been completely read
**		• -1 = an error occurred
**
**/
#include <stdio.h> // don't forget to remove
#include "get_next_line.h"

int get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		*extra[FD_MAX];

	//printf(RED"fd:"WHT" %d\n", fd);
	if (!line || fd < 0 || read(fd, buf, 0) < 0) //error check
		return(-1);
	//printf(RED"extra[fd]: "WHT"%s\n", extra[fd]);
	//printf(GRY"*line:"WHT" %s\n", *line);
	if(!read(fd, buf, BUFF_SIZE))
	{
		extra[fd] = "\0";
		return(0);
	}
	//printf(GRY"stored in extra["WHT"%d"GRY"]: "WHT"%s\n", fd, extra[fd]);
	if (extra[fd])
	{
		*line = ft_strdup(extra[fd]);
		extra[fd] = "\0";
	}
	while (1)
	{
		if (!(ft_strnchr(buf, '\n', BUFF_SIZE))) // if there is NOT a '\n' in buf
		{
			if (!*line)
				*line = ft_strdup(buf);
			else
				*line = ft_strjoin(*line, buf); // put buf into *line
			//printf(GRY"stored in *line:"WHT" %s\n", *line);
			if (!read(fd, buf, BUFF_SIZE))
				return(1);
		}
		else
		{
			if(!*line)
				*line = "\0";
			*line = ft_strcjoin(*line, buf, '\n');
			extra[fd] = ft_strdup((ft_strchr(buf, '\n')) + 1);
			return(1);
		}
		//printf(GRY"  stored in buf:"WHT" %s\n", buf);
		//if (read(fd, buf, BUFF_SIZE) < BUFF_SIZE)
		//	return (1);
		//read(fd, buf, BUFF_SIZE);
	}
	return (-1);
}

int	main(void) // Don't forget to remove main()
{
	char **line;
 	char *file = "limerick.txt";
	int fd = open(file, O_RDONLY);
	int i = 1;

	while((i = get_next_line(fd, line)))
	{
		//i = get_next_line(fd, line);
		printf(WHT"%s "RED"%d\n"WHT, *line, i);
	}
	printf(RED"%d\n", i);
	return(0);
}

