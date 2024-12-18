/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:14:01 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/18 09:49:25 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "so_long.h"

void	build_image(t_data *data, int posX, int posY, char tile_type)
{
	char	*pixel;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = data->addr + (posX * TILE_SIZE * (data->bits_per_pixel / 8)) + (posY * TILE_SIZE * data->line_length) + (y * data->line_length + x * (data->bits_per_pixel / 8));
			if (tile_type == '0')
				*(unsigned int*)pixel = 0x000000;
			if (tile_type == '1')
				*(unsigned int*)pixel = 0xFF0000;
			if (tile_type == 'C')
				*(unsigned int*)pixel = 0xFFFF00;
			if (tile_type == 'E')
				*(unsigned int*)pixel = 0x00FF00;
			if (tile_type == 'P')
				*(unsigned int*)pixel = 0x0000FF;
			x++;
		}
		y++;
	}
}

int	move_player(t_data *data, int dir)
{
	char	*pixel = NULL;
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
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = data->addr + (test_posX * TILE_SIZE * (data->bits_per_pixel / 8)) + (test_posY * TILE_SIZE * data->line_length) + (y * data->line_length + x * (data->bits_per_pixel / 8));	
			if (*(unsigned int*)pixel == 0xFF0000)
				return (0);
			else
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	input(int key_pressed, void *param)
{
	t_data	*data;
	int		res;
	
	data = param;
	if (key_pressed == 65362)
	{
		res = move_player(data, 1);
		if (res)
		{
			build_image(data, (data->posX), (data->posY), '0');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			build_image(data, (data->posX), (--data->posY), 'P');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
	if (key_pressed == 65363)
	{
		res = move_player(data, 2);
		if (res)
		{
			build_image(data, (data->posX), (data->posY), '0');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			build_image(data, (++data->posX), (data->posY), 'P');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
	if (key_pressed == 65364)
	{
		res = move_player(data, 3);
		if (res)
		{
			build_image(data, (data->posX), (data->posY), '0');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			build_image(data, (data->posX), (++data->posY), 'P');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
	if (key_pressed == 65361)
	{
		res = move_player(data, 4);
		if (res)
		{
			build_image(data, (data->posX), (data->posY), '0');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			build_image(data, (--data->posX), (data->posY), 'P');
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
	return (1);
}

void	put_block(char tile_type, t_data data, int posX, int posY)
{
	build_image(&data, posX, posY, tile_type);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
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

t_data	parse_map(char *map, t_data data)
{
	int			fd;
	char		*line;
	int			posY;

	posY = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);

	data.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	put_line(line, data, posY);
	posY++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			data = put_line(line, data, posY);
			posY++;
		}
	}
	return (data);
}

t_data	handle_keypress(t_data data)
{
	mlx_hook(data.win, KeyPress, KeyPressMask, input, &data);
	return (data);
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (0);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so_long");
	data = parse_map(av[1], data);
	handle_keypress(data);
	mlx_loop(data.mlx);
	return (0);
}