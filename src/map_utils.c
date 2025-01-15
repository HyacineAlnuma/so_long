/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:54:11 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/15 10:54:57 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	determine_line_nb(char *map_file)
{
	int		line_nb;
	int		fd;
	char	*line;

	line_nb = 0;
	fd = open(map_file, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Map error", 2);
		return (0);
	}
	line = get_next_line(fd);
	if (line)
		line_nb++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			line_nb++;
	}
	close(fd);
	return (line_nb);
}

char	**read_map(char *map_file, t_game *game)
{
	int		fd;
	int		i;

	fd = open(map_file, O_RDONLY);
	if (!fd || fd == -1)
	{
		ft_putstr_fd("Error while openning the map", 2);
		exit (EXIT_FAILURE);
	}
	game->height = determine_line_nb(map_file);
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!(game->map))
		return (NULL);
	game->map[0] = get_next_line(fd);
	game->width = ft_strlen(game->map[0]);
	i = 0;
	while (++i < game->height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			return (NULL);
	}
	game->map[i] = NULL;
	close(fd);
	return (game->map);
}

void	find_exit_pos(char **map, int *pos)
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
			if (map[i][j] == 'E')
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

char	**copy_map(char **map, int map_size)
{
	int		i;
	char	**map_cpy;

	i = 0;
	map_cpy = (char **)malloc(sizeof(char *) * (map_size + 1));
	if (!map_cpy)
	{
		free_map(map);
		ft_putstr_fd("Error: Malloc failed", 2);
		exit(EXIT_FAILURE);
	}
	while (i < map_size)
	{
		map_cpy[i] = ft_strdup(map[i]);
		if (!map_cpy)
		{
			free_map(map_cpy);
			return (NULL);
		}
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}
