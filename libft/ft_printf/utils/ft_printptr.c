/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:23:16 by halnuma           #+#    #+#             */
/*   Updated: 2024/11/20 09:32:04 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printptr(size_t n, char *base)
{
	if (!n)
	{
		ft_printstr("(nil)");
		return (5);
	}
	else
	{
		ft_printstr("0x");
		ft_putnbr_base(n, base);
		return (ft_ptrlen(n, base, 0) + 2);
	}
}

void	ft_putnbr_base(size_t n, char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (n < 0)
	{
		ft_printchar('-');
		ft_putnbr_base(n * -1, base);
	}
	else
	{
		if (n >= base_len)
		{
			ft_putnbr_base((n / base_len), base);
			ft_printchar(base[n % base_len]);
		}
		else
		{
			ft_printchar(base[n % base_len]);
		}
	}
}

int	ft_ptrlen(size_t n, char *base, int count)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (n < 0)
	{
		count++;
		return (ft_ptrlen(n * -1, base, count));
	}
	else
	{
		if (n >= base_len)
		{
			count++;
			return (ft_ptrlen((n / base_len), base, count));
		}
		else
		{
			count++;
			return (count);
		}
	}
}
