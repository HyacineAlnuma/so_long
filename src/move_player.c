/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:50:36 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 16:18:18 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	move_player(t_game *game, int pos_x, int pos_y, int key_pressed)
{
	char	*steps;

	if (key_pressed == KEY_RIGHT)
		game->direction = KEY_RIGHT;
	if (key_pressed == KEY_LEFT)
		game->direction = KEY_LEFT;
	game->map[game->pos_y][game->pos_x] = '0';
	display_tile(game, game->pos_x, game->pos_y, '0');
	game->pos_x = pos_x;
	game->pos_y = pos_y;
	display_tile(game, game->pos_x, game->pos_y, 'P');
	game->map[game->pos_y][game->pos_x] = 'P';
	game->steps++;
	printf("Steps: %d\n", game->steps);
	steps = ft_itoa(game->steps);
	display_tile(game, 0, 0, '1');
	mlx_string_put(game->mlx, game->win, 15, 25, 0xFFFFD4A3, "Steps:");
	mlx_string_put(game->mlx, game->win, 15, 45, 0xFFFFD4A3, steps);
	free(steps);
}

char	test_next_tile(t_game *game, int key_pressed)
{
	int		x;
	int		y;
	int		test_x;
	int		test_y;

	x = 0;
	y = 0;
	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_UP)
		test_y--;
	if (key_pressed == KEY_LEFT)
		test_x--;
	if (key_pressed == KEY_RIGHT)
		test_x++;
	if (key_pressed == KEY_DOWN)
		test_y++;
	if (game->map[test_y][test_x] == '1' || game->map[test_y][test_x] == 'E')
		return ('1');
	if (game->map[test_y][test_x] == 'C')
		return ('C');
	if (game->map[test_y][test_x] == 'e')
		return ('e');
	else
		return ('0');
}

void	handle_input(t_game *game, int pos_x, int pos_y, int key_pressed)
{
	char	next_tile;
	int		exit;

	next_tile = test_next_tile(game, key_pressed);
	if (next_tile == 'e')
	{
		game->map[game->pos_y][game->pos_x] = '0';
		display_tile(game, game->pos_x, game->pos_y, '0');
		end_level(game);
		return ;
	}
	if (next_tile == 'C')
	{
		game->map[pos_y][pos_x] = 'P';
		exit = check_if_exit_possible(game->map);
		if (exit)
			convert_exit(game);
	}
	if (next_tile == '0' || next_tile == 'C')
		move_player(game, pos_x, pos_y, key_pressed);
}

int	key_hook(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	if (!game->end)
	{
		if (key_pressed == KEY_UP)
			handle_input(game, game->pos_x, (game->pos_y - 1), key_pressed);
		if (key_pressed == KEY_RIGHT)
			handle_input(game, (game->pos_x + 1), game->pos_y, key_pressed);
		if (key_pressed == KEY_DOWN)
			handle_input(game, game->pos_x, (game->pos_y + 1), key_pressed);
		if (key_pressed == KEY_LEFT)
			handle_input(game, (game->pos_x - 1), game->pos_y, key_pressed);
	}
	if (key_pressed == ESCAPE)
		exit_game(game);
	return (1);
}
