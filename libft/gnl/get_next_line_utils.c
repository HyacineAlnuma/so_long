/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:30:14 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/16 14:54:03 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	bytes_nb;

	bytes_nb = nmemb * size;
	if (nmemb * size != 0)
		if (nmemb > SIZE_MAX / size)
			return (NULL);
	res = malloc(bytes_nb);
	if (!res)
		return (NULL);
	ft_bzero(res, bytes_nb);
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	size_t	size;
	char	*res;
	size_t	i;
	int		j;
	size_t	s1_size;

	s1_size = 0;
	if (s1)
		s1_size = ft_strlen(s1);
	size = s1_size + n + 1;
	res = (char *)ft_calloc(sizeof(char), size);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[j])
			res[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] && j < n)
		res[i++] = s2[j++];
	return (res);
}

char	*join_line(char	*line, char *buffer, int n)
{
	char	*joined_line;

	joined_line = ft_strnjoin(line, buffer, n);
	if (!joined_line)
	{
		free(line);
		return (NULL);
	}
	if (line)
		free(line);
	return (joined_line);
}
