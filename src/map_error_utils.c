/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:42:50 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 16:47:10 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

int	check_borders(char **map)
{
	int	i;
	int	width;
	int	height;

	i = -1;
	while (map[0][++i])
	{
		if (map[0][i] != '1' && map[0][i] != '\n')
			return (0);
	}
	width = i - 2;
	i = -1;
	while (map[++i])
	{
		if (map[i][0] != '1' || map[i][width] != '1')
			return (0);
	}
	height = i - 1;
	i = -1;
	while (map[height][++i])
	{
		if (map[height][i] != '1' && map[0][i] != '\n')
			return (0);
	}
	return (1);
}

int	check_tile_validity(char c)
{
	if (c != '1' && c != '0' && c != 'C' && c != 'E' && c != 'P' && c != '\n')
		return (0);
	return (1);
}

int	check_map_shape(char **map)
{
	int	i;
	int	j;
	int	width;

	width = 0;
	while (map[0][width] != '\n')
		width++;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_tile_validity(map[i][j]))
				return (0);
			j++;
		}
		if (map[i][j - 1] == '\n')
			j--;
		if (j != width)
			return (0);
		i++;
	}
	return (1);
}

int	check_valid_player_and_cons(char **map)
{
	int	i;
	int	j;
	int	player;
	int	cons;

	player = 0;
	cons = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == 'P' && player))
				return (0);
			if (map[i][j] == 'P' && !player)
				player++;
			if (map[i][j] == 'C')
				cons++;
		}
	}
	if (player == 0 || cons == 0)
		return (0);
	return (1);
}

int	check_valid_exit(char **map)
{
	int	i;
	int	j;
	int	exit;

	exit = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == 'E' && exit))
				return (0);
			if (map[i][j] == 'E' && !exit)
				exit++;
		}
	}
	if (exit == 0)
		return (0);
	return (1);
}
