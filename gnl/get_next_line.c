/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:30:01 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/16 14:52:59 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	int			nl;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	nl = 0;
	line = NULL;
	if (ft_strlen(buffer[fd]) > 0)
	{
		nl = check_if_nl(buffer[fd]);
		line = process_buffer(line, buffer[fd]);
		if (!line)
			return (NULL);
	}
	if (!nl)
	{
		line = next_line(fd, line, buffer[fd], nl);
		if (!line)
			return (NULL);
	}
	return (line);
}

int	check_if_nl(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*next_line(int fd, char *line, char *buffer, int nl)
{
	int			read_size;

	read_size = BUFFER_SIZE;
	while (!nl && read_size == BUFFER_SIZE)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0 && line)
			free(line);
		if (read_size < 0)
			return (NULL);
		if (read_size == 0)
			return (line);
		nl = check_if_nl(buffer);
		line = process_buffer(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*process_buffer(char *line, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			line = join_line(line, buffer, (i + 1));
			if (!line)
				return (NULL);
			buffer = shift_buffer(buffer, i + 1);
			return (line);
		}
		i++;
	}
	line = join_line(line, buffer, i);
	if (!line)
		return (NULL);
	buffer = shift_buffer(buffer, i);
	return (line);
}

char	*shift_buffer(char *buffer, int i)
{
	int	j;

	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	while (buffer[j])
		buffer[j++] = '\0';
	return (buffer);
}
