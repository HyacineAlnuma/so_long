/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:01 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/18 17:00:28 by halnuma          ###   ########.fr       */
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
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.wall, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.cons, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.exit, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.player, (posX * TILE_SIZE), (posY * TILE_SIZE));
}

void	build_end_image(t_data *data, int posX, int posY, char tile_type)
{
	if (tile_type == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.empty_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.wall_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
	if (tile_type == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->sprites.player_end, (posX * TILE_SIZE), (posY * TILE_SIZE));
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
	if (data->map[test_posY][test_posX] == '1')
		return (0);
	if (data->map[test_posY][test_posX] == 'C')
		return (2);
	if (data->map[test_posY][test_posX] == 'E')
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
	int	i;
	int	j;

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

int	input(int key_pressed, void *param)
{
	t_data	*data;
	int		res;
	int		exit;
	
	data = param;
	if (data->end)
	{
		if (key_pressed == KEY_UP)
		{
			res = test_move(data, 1);
			if (res == 3)
			{
				exit = check_if_exit_possible(data->map);
				if (exit)
				{
					data->map[data->posY][data->posX] = '0';
					data->map[--data->posY][data->posX] = 'P';
					build_image(data, data->posX, data->posY, '0');
					end_level(data);
				}
				return (1);
			}
			if (res && res != 3)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, data->posX, --data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
			}
		}
		if (key_pressed == KEY_RIGHT)
		{
			res = test_move(data, 2);
			if (res == 3)
			{
				exit = check_if_exit_possible(data->map);
				if (exit)
				{
					data->map[data->posY][data->posX] = '0';
					data->map[data->posY][++data->posX] = 'P';
					build_image(data, data->posX, data->posY, '0');
					end_level(data);
				}
				return (1);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, ++data->posX, data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
			}
		}
		if (key_pressed == KEY_DOWN)
		{
			res = test_move(data, 3);
			if (res == 3)
			{
				exit = check_if_exit_possible(data->map);
				if (exit)
				{
					data->map[data->posY][data->posX] = '0';
					data->map[++data->posY][data->posX] = 'P';
					build_image(data, data->posX, data->posY, '0');
					end_level(data);
				}
				return (1);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, data->posX, ++data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
			}
		}
		if (key_pressed == KEY_LEFT)
		{
			res = test_move(data, 4);
			if (res == 3)
			{
				exit = check_if_exit_possible(data->map);
				if (exit)
				{
					data->map[data->posY][data->posX] = '0';
					data->map[data->posY][--data->posX] = 'P';
					build_image(data, data->posX, data->posY, '0');
					end_level(data);
				}
				return (1);
			}
			if (res)
			{
				data->map[data->posY][data->posX] = '0';
				build_image(data, data->posX, data->posY, '0');
				build_image(data, --data->posX, data->posY, 'P');
				data->map[data->posY][data->posX] = 'P';
			}
		}
	}
	return (1);
}

void	put_block(char tile_type, t_data data, int posX, int posY)
{
	build_image(&data, posX, posY, tile_type);
	//mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
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
			//ft_printf("%d %d\n", data.posX, data.posY);
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

// t_data	parse_map(char *map, t_data data)
// {
// 	int			fd;
// 	char		*line;
// 	int			posY;

// 	posY = 0;
// 	fd = open(map, O_RDONLY);
// 	line = get_next_line(fd);

// 	data.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
// 	put_line(line, data, posY);
// 	posY++;
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		if (line)
// 		{
// 			data = put_line(line, data, posY);
// 			posY++;
// 		}
// 	}
// 	return (data);
// }

t_data	handle_keypress(t_data data)
{

	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
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

void	read_map(char *map_file, t_data *data)
{
	int		fd;
	int		i;

	data->height = determine_line_nb(map_file);
	data->map = (char **)malloc(sizeof(char *) * (data->height  + 1));
	fd = open(map_file, O_RDONLY);
	// if (!fd)
	// {
	// 	free(data.map);
	// 	ft_putstr_fd("Map error", 2);
	// 	return (NULL);
	// }
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

int	main(int ac, char **av)
{
	t_data		data;
	int 		x;
	int			y;

	x = 0;
	y = 0;
	if (ac != 2)
		return (0);
	read_map(av[1], &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, ((data.width- 1) * TILE_SIZE), (data.height * TILE_SIZE), "Il faut sauver le soldat capybara");
	data.img = mlx_new_image(data.mlx, ((data.width - 1) * TILE_SIZE), (data.height * TILE_SIZE));
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.end = 1;
	data.sprites.wall = mlx_xpm_file_to_image(data.mlx, "sprites/wall.xpm", &x, &y);
	data.sprites.empty = mlx_xpm_file_to_image(data.mlx, "sprites/empty.xpm", &x, &y);
	data.sprites.player = mlx_xpm_file_to_image(data.mlx, "sprites/player.xpm", &x, &y);
	data.sprites.cons = mlx_xpm_file_to_image(data.mlx, "sprites/cons.xpm", &x, &y);
	data.sprites.exit = mlx_xpm_file_to_image(data.mlx, "sprites/exit.xpm", &x, &y);
	data.sprites.wall_end = mlx_xpm_file_to_image(data.mlx, "sprites/wall_end.xpm", &x, &y);
	data.sprites.empty_end = mlx_xpm_file_to_image(data.mlx, "sprites/empty_end.xpm", &x, &y);
	data.sprites.player_end = mlx_xpm_file_to_image(data.mlx, "sprites/player_end.xpm", &x, &y);
	data.sprites.victory = mlx_xpm_file_to_image(data.mlx, "sprites/victory.xpm", &x, &y);
	data = put_lines(data);
	handle_keypress(data);
	mlx_loop(data.mlx);
	free(data.map);
	return (0);
}