/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:46:51 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 16:18:13 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	load_sprites(t_game *game, int x, int y)
{
	game->spr.wall = mlx_xpm_file_to_image(game->mlx, WALL, &x, &y);
	game->spr.empty = mlx_xpm_file_to_image(game->mlx, EMPTY, &x, &y);
	game->spr.p_r = mlx_xpm_file_to_image(game->mlx, P_R, &x, &y);
	game->spr.p_l = mlx_xpm_file_to_image(game->mlx, P_L, &x, &y);
	game->spr.cons = mlx_xpm_file_to_image(game->mlx, CONS, &x, &y);
	game->spr.exit_o = mlx_xpm_file_to_image(game->mlx, EXIT_O, &x, &y);
	game->spr.exit_c = mlx_xpm_file_to_image(game->mlx, EXIT_C, &x, &y);
	game->spr.exit_e = mlx_xpm_file_to_image(game->mlx, EXIT_E, &x, &y);
	game->spr.wall_e = mlx_xpm_file_to_image(game->mlx, WALL_E, &x, &y);
	game->spr.empty_e = mlx_xpm_file_to_image(game->mlx, EMPTY_E, &x, &y);
	game->spr.victory = mlx_xpm_file_to_image(game->mlx, VICTORY, &x, &y);
}

void	run_game(t_game *game)
{
	int	x;
	int	y;
	int	size_x;
	int	size_y;

	x = 0;
	y = 0;
	size_x = ((game->width - 1) * TILE_SIZE);
	size_y = (game->height * TILE_SIZE);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, size_x, size_y, GAME_NAME);
	game->end = 0;
	game->steps = 0;
	game->direction = KEY_RIGHT;
	load_sprites(game, x, y);
	game = display_map(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_hook, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop(game->mlx);
}
