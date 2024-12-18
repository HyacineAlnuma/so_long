/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:38:00 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/18 09:46:37 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 64
# define SCREEN_WIDTH 3840
# define SCREEN_HEIGHT 2160

typedef struct s_data
{
	void	*mlx;
	char	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		posX;
	int		posY;
	char	**map;
}	t_data;

#endif