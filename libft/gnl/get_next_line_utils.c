/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:30:14 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/18 11:45:52 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

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
