/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/08 09:31:51 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

int	main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
	{
		ft_putstr_fd("Error: One argument needed", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.ber needed)", 2);
		exit(EXIT_FAILURE);
	}
	check_map_errors(&game, av[1]);
	run_game(&game);
	return (0);
}

int	check_file_extension(char *filename)
{
	char	*file_extension;

	file_extension = ft_strchr(filename, '.');
	if (!file_extension)
		return (0);
	if (ft_strncmp(file_extension, ".ber", 5))
		return (0);
	return (1);
}

void	check_map_errors(t_game *game, char *map_file)
{
	if (!read_map(map_file, game))
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		exit(EXIT_FAILURE);
	}
	if (game->width > 60 || game->height > 33)
	{
		free_map(game->map);
		ft_putstr_fd("Error: The map is too big", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_map_validity(game->map))
	{
		free_map(game->map);
		ft_putstr_fd("Error: The map is not valid", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_map_solvability(game->map, game->height))
	{
		free_map(game->map);
		ft_putstr_fd("Error: The map is not solvable", 2);
		exit(EXIT_FAILURE);
	}
}

int	check_map_validity(char **map)
{
	if (!check_borders(map) || !check_map_shape(map))
		return (0);
	if (!check_valid_player_and_cons(map) || !check_valid_exit(map))
		return (0);
	return (1);
}
