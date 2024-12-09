/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:25:42 by halnuma           #+#    #+#             */
/*   Updated: 2024/11/20 09:59:13 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printhex(unsigned int n, int base_case)
{
	char	*base;

	if (!n)
	{
		ft_printchar('0');
		return (1);
	}
	if (base_case == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_printhex((n / 16), base_case);
		ft_printchar(base[n % 16]);
	}
	else
		ft_printchar(base[n % 16]);
	return (ft_hexlen(n, base, 0));
}

int	ft_hexlen(unsigned int n, char *base, int count)
{
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		count++;
		return (ft_hexlen((n / base_len), base, count));
	}
	else
	{
		count++;
		return (count);
	}
}
