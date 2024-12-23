/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:48:50 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 16:06:12 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	end_level(t_game *game)
{
	char	*steps;
	int		x;
	int		y;

	x = ((game->width - 5) * TILE_SIZE) / 2;
	y = ((game->height - 4) * TILE_SIZE) / 2;
	display_end_map(game);
	game->end = 1;
	game->steps++;
	ft_printf("Steps :%d\n", game->steps);
	ft_printf("Bien vu chef tu régales\n");
	steps = ft_itoa(game->steps);
	display_tile(game, 0, 0, '1');
	mlx_string_put(game->mlx, game->win, 15, 25, 0xFFFFD4A3, "Steps:");
	mlx_string_put(game->mlx, game->win, 15, 45, 0xFFFFD4A3, steps);
	free(steps);
	mlx_put_image_to_window(game->mlx, game->win, game->spr.victory, x, y);
}

void	destroy_images(t_game *game)
{
	if (game->spr.cons)
		mlx_destroy_image(game->mlx, game->spr.cons);
	if (game->spr.empty)
		mlx_destroy_image(game->mlx, game->spr.empty);
	if (game->spr.empty_e)
		mlx_destroy_image(game->mlx, game->spr.empty_e);
	if (game->spr.exit_o)
		mlx_destroy_image(game->mlx, game->spr.exit_o);
	if (game->spr.exit_c)
		mlx_destroy_image(game->mlx, game->spr.exit_c);
	if (game->spr.exit_e)
		mlx_destroy_image(game->mlx, game->spr.exit_e);
	if (game->spr.p_r)
		mlx_destroy_image(game->mlx, game->spr.p_r);
	if (game->spr.p_l)
		mlx_destroy_image(game->mlx, game->spr.p_l);
	if (game->spr.victory)
		mlx_destroy_image(game->mlx, game->spr.victory);
	if (game->spr.wall)
		mlx_destroy_image(game->mlx, game->spr.wall);
	if (game->spr.wall_e)
		mlx_destroy_image(game->mlx, game->spr.wall_e);
}

int	exit_game(t_game *game)
{
	free_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	destroy_images(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	convert_exit(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
			{
				game->map[i][j] = 'e';
				display_tile(game, j, i, 'e');
				break ;
			}
			j++;
		}
		i++;
	}
}

int	check_if_exit_possible(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
