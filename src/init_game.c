/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:46:51 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/08 12:56:38 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

int	load_sprites_1(t_game *game, int x, int y)
{
	game->spr.wall = mlx_xpm_file_to_image(game->mlx, WALL, &x, &y);
	if (!game->spr.wall)
		return (0);
	game->spr.empty = mlx_xpm_file_to_image(game->mlx, EMPTY, &x, &y);
	if (!game->spr.empty)
		return (0);
	game->spr.p_r = mlx_xpm_file_to_image(game->mlx, P_R, &x, &y);
	if (!game->spr.p_r)
		return (0);
	game->spr.p_l = mlx_xpm_file_to_image(game->mlx, P_L, &x, &y);
	if (!game->spr.p_l)
		return (0);
	game->spr.cons = mlx_xpm_file_to_image(game->mlx, CONS, &x, &y);
	if (!game->spr.cons)
		return (0);
	return (1);
}

int	load_sprites_2(t_game *game, int x, int y)
{
	game->spr.exit_o = mlx_xpm_file_to_image(game->mlx, EXIT_O, &x, &y);
	if (!game->spr.exit_o)
		return (0);
	game->spr.exit_c = mlx_xpm_file_to_image(game->mlx, EXIT_C, &x, &y);
	if (!game->spr.exit_c)
		return (0);
	game->spr.exit_e = mlx_xpm_file_to_image(game->mlx, EXIT_E, &x, &y);
	if (!game->spr.exit_e)
		return (0);
	game->spr.wall_e = mlx_xpm_file_to_image(game->mlx, WALL_E, &x, &y);
	if (!game->spr.wall_e)
		return (0);
	game->spr.empty_e = mlx_xpm_file_to_image(game->mlx, EMPTY_E, &x, &y);
	if (!game->spr.empty_e)
		return (0);
	game->spr.victory = mlx_xpm_file_to_image(game->mlx, VICTORY, &x, &y);
	if (!game->spr.victory)
		return (0);
	return (1);
}

void	init_game(t_game *game, int size_x, int size_y)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->win = mlx_new_window(game->mlx, size_x, size_y, GAME_NAME);
	if (!game->win)
	{
		ft_putstr_fd("Error while loading window", 2);
		free_map(game->map);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->end = 0;
	game->steps = 0;
	game->direction = KEY_RIGHT;
	if (!load_sprites_1(game, x, y) || !load_sprites_2(game, x, y))
	{
		ft_putstr_fd("Error while loading sprites", 2);
		exit_game(game);
		exit(EXIT_FAILURE);
	}
}

void	run_game(t_game *game)
{
	int	size_x;
	int	size_y;

	size_x = ((game->width - 1) * TILE_SIZE);
	size_y = (game->height * TILE_SIZE);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error while loading mlx", 2);
		free_map(game->map);
		exit(EXIT_FAILURE);
	}
	init_game(game, size_x, size_y);
	game = display_map(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_hook, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop(game->mlx);
}
