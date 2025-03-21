/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:56 by halnuma           #+#    #+#             */
/*   Updated: 2024/11/07 16:32:56 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c < '0' || c > 'z' || (c > 'Z' && c < 'a') || (c > '9' && c < 'A'))
	{
		return (0);
	}
	return (1);
}
