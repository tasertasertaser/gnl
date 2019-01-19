/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschulle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:13:59 by cschulle          #+#    #+#             */
/*   Updated: 2019/01/18 21:08:25 by cschulle         ###   ########.fr       */
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
	size_t			i;

	buf[BUFF_SIZE] = '\0';
	if (!line || fd < 0 || read(fd, buf, 0) < 0) //error check
		return(-1);
	*line = NULL;
	if (extra[fd])
	{
		*line = ft_strdup(extra[fd]);
		extra[fd] = "\0";
	}
	while ((i = read(fd, buf, BUFF_SIZE)))
	{
		//printf("buf: %s\n", buf);
		if (!(ft_strnchr(buf, '\n', BUFF_SIZE))) // if there is NOT a '\n' in buf
		{
			if (!*line)
				*line = ft_strdup(buf);
			else
				*line = ft_strjoin(*line, buf); // put buf into *line
		//	printf(GRY"*line: %s\n", *line);
		}
		else
		{
			if(!*line)
				*line = "\0";
			*line = ft_strcjoin(*line, buf, '\n');
			extra[fd] = ft_strdup((ft_strchr(buf, '\n')) + 1);	
			return(1);
		}
		ft_bzero(buf, BUFF_SIZE);
	}
//	printf(GRY"line: %s\n", *line);
	if (*line == NULL || **line == '\0')
		return (0);
	else
		return(1);
//	extra[fd] = "\0";
//	return (0);
}
/*
int	main(void) // Don't forget to remove main()
{
	char **line;
 	char *file = "waffles.txt";
	int fd = 0; //open(file, O_RDONLY);
	int i = 1;

	while((i = get_next_line(fd, line)))
		printf(WHT"%s "RED"%d\n"WHT, *line, i);
	//printf("%s\n", *line);
	printf(RED"%d\n"WHT, i);
	return(0);
}*/
