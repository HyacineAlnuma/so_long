/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:38:00 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/08 12:23:46 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define GAME_NAME "Il faut sauver le soldat Capybara"

# define CONS "sprites/cons.xpm"
# define EMPTY_E "sprites/empty_e.xpm"
# define EMPTY "sprites/empty.xpm"
# define EXIT_C	 "sprites/exit_c.xpm"
# define EXIT_E "sprites/exit_e.xpm"
# define EXIT_O "sprites/exit_o.xpm"
# define P_L "sprites/p_l.xpm"
# define P_R "sprites/p_r.xpm"
# define VICTORY "sprites/victory.xpm"
# define WALL_E "sprites/wall_e.xpm"
# define WALL "sprites/wall.xpm"

# define TILE_SIZE 64
# define SCREEN_WIDTH 3840
# define SCREEN_HEIGHT 2160
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define ESCAPE 65307

typedef struct s_sprites
{
	void	*wall;
	void	*empty;
	void	*p_r;
	void	*p_l;
	void	*cons;
	void	*exit_o;
	void	*exit_c;
	void	*exit_e;
	void	*wall_e;
	void	*empty_e;
	void	*victory;
}	t_sprites;

typedef struct s_game
{
	void		*mlx;
	char		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			width;
	int			height;
	int			endian;
	int			pos_x;
	int			pos_y;
	int			end;
	char		**map;
	int			steps;
	int			direction;
	t_sprites	spr;
}	t_game;

void	run_game(t_game *game);
void	init_game(t_game *game, int size_x, int size_y);
int		load_sprites_1(t_game *game, int x, int y);
int		load_sprites_2(t_game *game, int x, int y);
void	check_map_errors(t_game *game, char *map_file);
int		check_file_extension(char *filename);
int		check_map_solvability(char **map, int map_size);
char	**copy_map(char **map, int map_size);
int		check_recursive_result(char **map);
void	find_player_pos(char **map, int *pos);
void	pathing_recursive(char **map, int pos_x, int pos_y);
int		check_tile(char tile);
int		check_map_validity(char **map);
int		check_valid_player_and_cons(char **map);
int		check_valid_exit(char **map);
int		check_map_shape(char **map);
int		check_tile_validity(char c);
int		check_borders(char **map);
char	**read_map(char *map_file, t_game *game);
int		determine_line_nb(char *map_file);
t_game	*display_map(t_game *game);
t_game	*display_line(char *line, t_game *game, int pos_y);
int		key_hook(int key_pressed, void *param);
void	handle_input(t_game *game, int pos_x, int pos_y, int key_pressed);
void	move_player(t_game *game, int pos_x, int pos_y, int key_pressed);
void	convert_exit(t_game *game);
void	find_exit_pos(char **map, int *pos);
int		exit_game(t_game *game);
void	destroy_images(t_game *game);
void	free_map(char **map);
void	end_level(t_game *game);
void	display_end_map(t_game *game);
int		check_if_exit_possible(char **map);
char	test_next_tile(t_game *game, int key_pressed);
void	display_end_tile(t_game *game, int pos_x, int pos_y, char tile_type);
void	display_tile(t_game *game, int pos_x, int pos_y, char tile_type);

#endif