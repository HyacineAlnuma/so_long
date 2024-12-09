/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:55:19 by halnuma           #+#    #+#             */
/*   Updated: 2024/11/11 16:10:23 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = ft_calloc(sizeof(char), size);
	if (!res)
		return (NULL);
	ft_strlcat(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}
