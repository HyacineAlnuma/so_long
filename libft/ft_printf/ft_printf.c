/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:02:04 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/03 16:55:51 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_print_vars(va_list vars, char next)
{
	int	count;

	count = 0;
	if (next == 'c')
		count += ft_printchar(va_arg(vars, int));
	else if (next == 's')
		count += ft_printstr(va_arg(vars, char *));
	else if (next == 'p')
		count += ft_printptr(va_arg(vars, size_t), "0123456789abcdef");
	else if (next == 'd')
		count += ft_printnbr(va_arg(vars, int));
	else if (next == 'i')
		count += ft_printnbr(va_arg(vars, int));
	else if (next == 'u')
		count += ft_printunbr(va_arg(vars, unsigned int));
	else if (next == 'x')
		count += ft_printhex(va_arg(vars, unsigned int), 0);
	else if (next == 'X')
		count += ft_printhex(va_arg(vars, unsigned int), 1);
	else
		count += ft_printchar('%');
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list			vars;
	size_t			i;
	int				count;

	count = 0;
	if (!input)
		return (-1);
	va_start(vars, input);
	i = 0;
	while (input[i])
	{
		if (input[i] != '%')
			count += ft_printchar(input[i]);
		else
		{
			count += ft_print_vars(vars, input[i + 1]);
			i++;
		}
		i++;
	}
	va_end(vars);
	return (count);
}
