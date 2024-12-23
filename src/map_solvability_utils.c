/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solvability_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:39:58 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 16:18:07 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

int	check_tile(char tile)
{
	if (tile == 'E')
		return (2);
	if (tile == '1' || tile == '2')
		return (0);
	return (1);
}

void	pathing_recursive(char **map, int pos_x, int pos_y)
{
	map[pos_x][pos_y] = '2';
	if (check_tile(map[pos_x + 1][pos_y]) == 2)
		map[pos_x + 1][pos_y] = '2';
	if (check_tile(map[pos_x + 1][pos_y]))
		pathing_recursive(map, (pos_x + 1), (pos_y));
	if (check_tile(map[pos_x][pos_y + 1]) == 2)
		map[pos_x][pos_y + 1] = '2';
	if (check_tile(map[pos_x][pos_y + 1]))
		pathing_recursive(map, (pos_x), (pos_y + 1));
	if (check_tile(map[pos_x - 1][pos_y]) == 2)
		map[pos_x - 1][pos_y] = '2';
	if (check_tile(map[pos_x - 1][pos_y]))
		pathing_recursive(map, (pos_x - 1), (pos_y));
	if (check_tile(map[pos_x][pos_y - 1]) == 2)
		map[pos_x][pos_y - 1] = '2';
	if (check_tile(map[pos_x][pos_y - 1]))
		pathing_recursive(map, (pos_x), (pos_y - 1));
}

int	check_recursive_result(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	find_player_pos(char **map, int *pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos[0] = j;
				pos[1] = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	check_map_solvability(char **map, int map_size)
{
	char	**test_map;
	int		pos[2];

	pos[0] = 0;
	pos[1] = 0;
	test_map = copy_map(map, map_size);
	if (!test_map)
		return (0);
	find_player_pos(test_map, pos);
	pathing_recursive(test_map, pos[0], pos[1]);
	if (!check_recursive_result(test_map))
	{
		free(test_map);
		return (0);
	}
	free_map(test_map);
	return (1);
}
