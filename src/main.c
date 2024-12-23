/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:01 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/23 11:56:10 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	build_image(t_data *data, int posX, int posY, char tile_type)
{
	if (tile_type == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.empty, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == '1')
	{
		if (posX == 0 && posY == 0)
			mlx_put_image_to_window(data->mlx, data->win, data->sprites.empty_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
		else
			mlx_put_image_to_window(data->mlx, data->win, data->sprites.wall, (posX * TILE_SIZE), (posY * TILE_SIZE));
	}
	if (tile_type == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.cons, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.exit_close, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'e')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.exit_open, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'P')
	{
		if (data->direction == 0)
			mlx_put_image_to_window(data->mlx, data->win, data->sprites.player_right, (posX * TILE_SIZE), (posY * TILE_SIZE));
		if (data->direction == 1)
			mlx_put_image_to_window(data->mlx, data->win, data->sprites.player_left, (posX * TILE_SIZE), (posY * TILE_SIZE));
	}
}

void	build_end_image(t_data *data, int posX, int posY, char tile_type)
{
	if (tile_type == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.empty_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.wall_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'e')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.exit_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
}

int	test_move(t_data *data, int dir)
{
	int		x;
	int		y;
	int		test_posX;
	int		test_posY;

	x = 0;
	y = 0;
	test_posY = data->posY;
	test_posX = data->posX;
	if (dir == 1)
		test_posY--;
	if (dir == 4)
		test_posX--;
	if (dir == 2)
		test_posX++;
	if (dir == 3)
		test_posY++;
	if (data->map[test_posY][test_posX] == '1' || data->map[test_posY][test_posX] == 'E')
		return (0);
	if (data->map[test_posY][test_posX] == 'C')
		return (2);
	if (data->map[test_posY][test_posX] == 'e')
		return (3);
	else
		return (1);
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

void	end_level(t_data *data)
{
	int		i;
	int		j;
	char	*steps;

	j = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			build_end_image(data, j, i, data->map[i][j]);
			j++;
		}
		i++;
	}
	data->end = 0;
	data->steps++;
	ft_printf("Steps :%d\n", data->steps);
	ft_printf("Bien vu chef tu régales\n");
	steps = ft_itoa(data->steps);
	build_image(data, 0, 0, '1');
	mlx_string_put(data->mlx, data->win, 15, 25, 0xFFFFD4A3, "Steps:");
	mlx_string_put(data->mlx, data->win, 15, 45, 0xFFFFD4A3, steps);
	free(steps);
	mlx_put_image_to_window(data->mlx, data->win, data->sprites.victory, ((data->width - 5)* TILE_SIZE) / 2, ((data->height - 4) * TILE_SIZE) / 2);
}

void	printmap(char **map)
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
			ft_printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
}

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

int	exit_game(t_data *data)
{
	free_map(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->sprites.cons)
		mlx_destroy_image(data->mlx, data->sprites.cons);
	if (data->sprites.empty)
		mlx_destroy_image(data->mlx, data->sprites.empty);
	if (data->sprites.empty_end)
		mlx_destroy_image(data->mlx, data->sprites.empty_end);
	if (data->sprites.exit_open)
		mlx_destroy_image(data->mlx, data->sprites.exit_open);
	if (data->sprites.exit_close)
		mlx_destroy_image(data->mlx, data->sprites.exit_close);
	if (data->sprites.exit_end)
		mlx_destroy_image(data->mlx, data->sprites.exit_end);
	if (data->sprites.player_right)
		mlx_destroy_image(data->mlx, data->sprites.player_right);
	if (data->sprites.player_left)
		mlx_destroy_image(data->mlx, data->sprites.player_left);
	if (data->sprites.victory)
		mlx_destroy_image(data->mlx, data->sprites.victory);
	if (data->sprites.wall)
		mlx_destroy_image(data->mlx, data->sprites.wall);
	if (data->sprites.wall_end)
		mlx_destroy_image(data->mlx, data->sprites.wall_end);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
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
				break;
			}
			j++;
		}
		i++;
	}
}

void convert_exit(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E')
			{
				data->map[i][j] = 'e';
				build_image(data, j, i, 'e');
				break;
			}
			j++;
		}
		i++;
	}
}

int	input(int key_pressed, void *param)
{
	t_data	*data;
	int		res;
	int		exit;
	char	*steps;
	
	data = param;
	if (data->end)
	{
		if (key_pressed == KEY_UP)
		{
			res = test_move(data, 1);
			if (res == 3)
			{
				data->map[data->posY][data->posX] = '0';
				//data->map[--data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				end_level(data);
				return (1);
			}
			if (res == 2)
			{
				data->map[data->posY - 1][data->posX] = 'P';
				exit = check_if_exit_possible(data->map);
				if (exit)
					convert_exit(data);
			}
			if (res && res != 3)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, data->posX, --data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
				data->steps++;
				printf("Steps: %d\n", data->steps);
				steps = ft_itoa(data->steps);
				build_image(data, 0, 0, '1');
				mlx_string_put(data->mlx, data->win, 15, 25, 0xFFFFD4A3, "Steps:");
				mlx_string_put(data->mlx, data->win, 15, 45, 0xFFFFD4A3, steps);
				free(steps);
			}
		}
		if (key_pressed == KEY_RIGHT)
		{
			res = test_move(data, 2);
			if (res == 3)
			{
				data->map[data->posY][data->posX] = '0';
				//data->map[data->posY][++data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				end_level(data);
				return (1);
			}
			if (res == 2)
			{
				data->map[data->posY][data->posX + 1] = 'P';
				exit = check_if_exit_possible(data->map);
				if (exit)
					convert_exit(data);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				data->direction = 0;
				build_image(data, data->posX, data->posY, '0');
				build_image(data, ++data->posX, data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
				data->steps++;
				printf("Steps: %d\n", data->steps);
				steps = ft_itoa(data->steps);
				build_image(data, 0, 0, '1');
				mlx_string_put(data->mlx, data->win, 15, 25, 0xFFFFD4A3, "Steps:");
				mlx_string_put(data->mlx, data->win, 15, 45, 0xFFFFD4A3, steps);
				free(steps);
			}
		}
		if (key_pressed == KEY_DOWN)
		{
			res = test_move(data, 3);
			if (res == 3)
			{
				data->map[data->posY][data->posX] = '0';
				//data->map[++data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				end_level(data);
				return (1);
			}
			if (res == 2)
			{
				data->map[data->posY + 1][data->posX] = 'P';
				exit = check_if_exit_possible(data->map);
				if (exit)
					convert_exit(data);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, data->posX, ++data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
				data->steps++;
				printf("Steps: %d\n", data->steps);
				steps = ft_itoa(data->steps);
				build_image(data, 0, 0, '1');
				mlx_string_put(data->mlx, data->win, 15, 25, 0xFFFFD4A3, "Steps:");
				mlx_string_put(data->mlx, data->win, 15, 45, 0xFFFFD4A3, steps);
				free(steps);
			}
		}
		if (key_pressed == KEY_LEFT)
		{
			res = test_move(data, 4);
			if (res == 3)
			{
				data->map[data->posY][data->posX] = '0';
				//data->map[data->posY][--data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				end_level(data);
				return (1);
			}
			if (res == 2)
			{
				data->map[data->posY][data->posX - 1] = 'P';
				exit = check_if_exit_possible(data->map);
				if (exit)
					convert_exit(data);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				data->direction = 1;
				build_image(data, data->posX, data->posY, '0');
				build_image(data, --data->posX, data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
				data->steps++;
				printf("Steps: %d\n", data->steps);
				steps = ft_itoa(data->steps);
				build_image(data, 0, 0, '1');
				mlx_string_put(data->mlx, data->win, 15, 25, 0xFFFFD4A3, "Steps:");
				mlx_string_put(data->mlx, data->win, 15, 45, 0xFFFFD4A3, steps);
				free(steps);
			}
		}
	}
	if (key_pressed == ESCAPE)
		exit_game(data);
	return (1);
}

void	put_block(char tile_type, t_data data, int posX, int posY)
{
	build_image(&data, posX, posY, tile_type);
}

t_data	put_line(char *line, t_data data, int posY)
{
	int			block;
	int			posX;

	block = 0;
	posX = 0;
	while(line[block])
	{
		if (line[block] == '0')
			put_block('0', data, posX, posY);
		if (line[block] == '1')
			put_block('1', data, posX, posY);
		if (line[block] == 'C')
			put_block('C', data, posX, posY);
		if (line[block] == 'E')
			put_block('E', data, posX, posY);
		if (line[block] == 'P')
		{
			data.posX = posX;
			data.posY = posY;
			put_block('P', data, posX, posY);
		}
		block++;
		posX++;
	}
	return(data);
}

t_data	put_lines(t_data data)
{
	int	line;

	line = 0;
	while(data.map[line])
	{
		data = put_line(data.map[line], data, line);
		line++;
	}
	return (data);
}

t_data	handle_keypress(t_data data)
{

	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	mlx_hook(data.win, DestroyNotify, 0, exit_game, &data);
	return (data);
}

int	determine_line_nb(char *map_file)
{
	int		line_nb;
	int		fd;
	char 	*line;

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

char	**read_map(char *map_file, t_data *data)
{
	int		fd;
	int		i;

	data->height = determine_line_nb(map_file);
	data->map = (char **)malloc(sizeof(char *) * (data->height  + 1));
	if (!(data->map))
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (!fd)
	{
		free(data->map);
		ft_putstr_fd("Error while openning the map", 2);
		return (NULL);
	}
	data->map[0] = get_next_line(fd);
	data->width = ft_strlen(data->map[0]);
	i = 1;
	while (i < data->height)
	{
		data->map[i] = get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
	close(fd);
	return (data->map);
}

int	check_if_finish(char **map)
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
			if (map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

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

int	check_map_content(char **map)
{
	int	i;
	int	j;
	int	player;
	int	exit;
	int	cons;

	player = 0;
	exit = 0;
	cons = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_tile_validity(map[i][j]))
				return (0);
			if (map[i][j] == 'P' && player == 1)
				return (0);
			if (map[i][j] == 'P' && player == 0)
				player++;
			if (map[i][j] == 'E' && exit == 1)
				return (0);
			if (map[i][j] == 'E' && exit == 0)
				exit++;
			if (map[i][j] == 'C')
				cons++;
			j++;
		}
		i++;
	}
	if (cons == 0 || player == 0 || exit == 0)
		return (0);
	return (1);
}

int	check_map_validity(char **map)
{
	if (!check_borders(map) || !check_map_shape(map) || !check_map_content(map))
		return (0);
	return (1);
}

int	check_tile(char tile)
{
	if (tile == 'E')
		return (2);
	if (tile == '1' || tile == '2')
		return (0);
	return (1);
}

void	pathing_recursive(char **map, int posX, int posY)
{
	map[posX][posY] = '2';
	if (check_tile(map[posX + 1][posY]) == 2)
		map[posX + 1][posY] = '2';
	if (check_tile(map[posX + 1][posY]))
		pathing_recursive(map, (posX + 1), (posY));
	if (check_tile(map[posX][posY + 1]) == 2)
		map[posX][posY + 1] = '2';
	if (check_tile(map[posX][posY + 1]))
		pathing_recursive(map, (posX), (posY + 1));
	if (check_tile(map[posX - 1][posY]) == 2)
		map[posX - 1][posY] = '2';
	if (check_tile(map[posX - 1][posY]))
		pathing_recursive(map, (posX - 1), (posY));
	if (check_tile(map[posX][posY - 1]) == 2)
		map[posX][posY - 1] = '2';
	if (check_tile(map[posX][posY - 1]))
		pathing_recursive(map, (posX), (posY - 1));
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
				break;
			}
			j++;
		}
		i++;
	}
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

char **copy_map(char **map, int map_size)
{
	int		i;
	char 	**map_cpy;

	i = 0;
	map_cpy = (char **)malloc(sizeof(char *) * (map_size + 1));
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
	// for (int i = 0; test_map[i]; i++)
	// 	ft_printf("%s", test_map[i]);
	if (!check_recursive_result(test_map))
	{
		free(test_map);
		return (0);
	}
	free_map(test_map);
	//free(test_map);
	return (1);
}

int	check_file_extension(char* filename)
{
	char	*file_extension;

	file_extension = ft_strchr(filename, '.');
	if (ft_strncmp(file_extension, ".ber", 5))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	int 		x;
	int			y;

	x = 0;
	y = 0;
	if (ac != 2)
		return (0);
	if (!check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.ber needed)", 2);
		return(0);
	}
	if (!read_map(av[1], &data))
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		return(0);
	}	
	if (data.width > 60 || data.height > 33)
	{
		free_map(data.map);
		ft_putstr_fd("Error: The map too big", 2);
		return(0);
	}
	if (!check_map_validity(data.map))
	{
		free_map(data.map);
		ft_putstr_fd("Error: The map is not valid", 2);
		return(0);
	}
	if (!check_map_solvability(data.map, data.height))
	{
		// for (int i = 0; data.map[i]; i++)
		// 	ft_printf("%s", data.map[i]);
		free_map(data.map);
		ft_putstr_fd("Error: The map is not solvable", 2);
		return(0);
	}
			// for (int i = 0; data.map[i]; i++)
		// 	ft_printf("%s", data.map[i]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, ((data.width- 1) * TILE_SIZE), (data.height * TILE_SIZE), "Il faut sauver le soldat capybara");
	//data.img = mlx_new_image(data.mlx, ((data.width - 1) * TILE_SIZE), (data.height * TILE_SIZE));
	//data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.end = 1;
	data.steps = 0;
	data.direction = 0;
	data.sprites.wall = mlx_xpm_file_to_image(data.mlx, "sprites/wall.xpm", &x, &y);
	data.sprites.empty = mlx_xpm_file_to_image(data.mlx, "sprites/empty.xpm", &x, &y);
	data.sprites.player_right = mlx_xpm_file_to_image(data.mlx, "sprites/player_right.xpm", &x, &y);
	data.sprites.player_left = mlx_xpm_file_to_image(data.mlx, "sprites/player_left.xpm", &x, &y);
	data.sprites.cons = mlx_xpm_file_to_image(data.mlx, "sprites/cons.xpm", &x, &y);
	data.sprites.exit_open = mlx_xpm_file_to_image(data.mlx, "sprites/exit_open.xpm", &x, &y);
	data.sprites.exit_close = mlx_xpm_file_to_image(data.mlx, "sprites/exit_close.xpm", &x, &y);
	data.sprites.exit_end = mlx_xpm_file_to_image(data.mlx, "sprites/exit_end.xpm", &x, &y);
	data.sprites.wall_end = mlx_xpm_file_to_image(data.mlx, "sprites/wall_end.xpm", &x, &y);
	data.sprites.empty_end = mlx_xpm_file_to_image(data.mlx, "sprites/empty_end.xpm", &x, &y);
	data.sprites.victory = mlx_xpm_file_to_image(data.mlx, "sprites/victory.xpm", &x, &y);
	data = put_lines(data);
	handle_keypress(data);
	mlx_loop(data.mlx);
	return (0);
}

//CLEAN