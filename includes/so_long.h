/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:38:00 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/18 16:53:09 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 64
# define SCREEN_WIDTH 3840
# define SCREEN_HEIGHT 2160
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_DOWN 65364

typedef struct s_sprites
{
	void	*wall;
	void	*empty;
	void	*player;
	void	*cons;
	void	*exit;	
	void	*wall_end;
	void	*empty_end;
	void	*player_end;
	void	*victory;
}	t_sprites;

typedef struct s_data
{
	void	*mlx;
	char	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
	int		posX;
	int		posY;
	int		end;
	char	**map;
	t_sprites sprites;
}	t_data;

#endif