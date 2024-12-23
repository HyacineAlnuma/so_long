/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:47:52 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 15:50:04 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	display_tile(t_game *game, int pos_x, int pos_y, char tile_type)
{
	int	x;
	int	y;

	x = pos_x * TILE_SIZE;
	y = pos_y * TILE_SIZE;
	if (tile_type == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.empty, x, y);
	if (tile_type == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.wall, x, y);
	if (pos_x == 0 && pos_y == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->spr.empty_e, x, y);
	if (tile_type == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.cons, x, y);
	if (tile_type == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.exit_c, x, y);
	if (tile_type == 'e')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.exit_o, x, y);
	if (tile_type == 'P')
	{
		if (game->direction == KEY_LEFT)
			mlx_put_image_to_window(game->mlx, game->win, game->spr.p_l, x, y);
		else
			mlx_put_image_to_window(game->mlx, game->win, game->spr.p_r, x, y);
	}
}

void	display_end_tile(t_game *game, int pos_x, int pos_y, char tile_type)
{
	int	x;
	int	y;

	x = pos_x * TILE_SIZE;
	y = pos_y * TILE_SIZE;
	if (tile_type == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.empty_e, x, y);
	if (tile_type == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.wall_e, x, y);
	if (tile_type == 'e')
		mlx_put_image_to_window(game->mlx, game->win, game->spr.exit_e, x, y);
}

void	display_end_map(t_game *game)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			display_end_tile(game, j, i, game->map[i][j]);
			j++;
		}
		i++;
	}
}

t_game	*display_line(char *line, t_game *game, int pos_y)
{
	int			tile;
	int			pos_x;

	tile = 0;
	pos_x = 0;
	while (line[tile])
	{
		if (line[tile] == '0')
			display_tile(game, pos_x, pos_y, '0');
		if (line[tile] == '1')
			display_tile(game, pos_x, pos_y, '1');
		if (line[tile] == 'C')
			display_tile(game, pos_x, pos_y, 'C');
		if (line[tile] == 'E')
			display_tile(game, pos_x, pos_y, 'E');
		if (line[tile] == 'P')
		{
			game->pos_x = pos_x;
			game->pos_y = pos_y;
			display_tile(game, pos_x, pos_y, 'P');
		}
		tile++;
		pos_x++;
	}
	return (game);
}

t_game	*display_map(t_game *game)
{
	int	line;

	line = 0;
	while (game->map[line])
	{
		game = display_line(game->map[line], game, line);
		line++;
	}
	return (game);
}
