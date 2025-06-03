/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/03 16:50:11 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include "libft.h"

# define TILE_SIZE 64

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		moves;
	int		collectable_counter;

	void	*img_wall;
	void	*img_background;

	int		player_x;
	int		player_y;
	void	*img_player;
	char	last_dir;
	int		player_index;
	void	*player_down[4];
	void	*player_up[4];
	void	*player_left[4];
	void	*player_right[4];
	int		player_timer;

	void	*img_collectable;
	int		collectable_index;
	void	*collectable[3];
	int		collectable_timer;

	void	*img_exit;
	int		exit_index;
	void	*exit[2];
	int		exit_timer;
	
	int		enemy_x;
	int		enemy_y;
	int		enemy_dx;
	int		enemy_dy;
	void	*img_enemy;
	int		enemy_timer;
}			t_game;

t_game	game_init(void *mlx, void *win, char **map);
char	**load_map(char *map_file);
char	**get_map(char **map, int fd);
char	**map_dup(t_game game);
char	*image_path(const char *prefix, int index, const char *suffix);
void	so_long(void *mlx, char **map);
void	arg_check(int argc, char **argv);
void	arg_error(char *error);
void	map_error(char **map, char *error);
void	ft_mlx_error(char **map);
void	ft_window_error(void *mlx, char **map);
void	ft_img_error(void *mlx, void *win, char **map);
void	free_map(char **map);
void	free_elements(int *elements);
void	exit_game(t_game *game);
void	render_map(t_game *game);
void	move_enemy(t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	enemy_animation(t_game *game);
void	clear_player_images(t_game *game);
void	clear_c_and_e_images(t_game *game);
void	clear_static_images(t_game *game);
void	player_movement_result(t_game *game, int dx, int dy, char next_tile);
void	enemy_movement_result(t_game *game, int dx, int dy, char tile);
void	enemy_bounce(t_game *game, int dx, int dy);
void	draw_player(t_game *game, void *img);
void	draw_tile(t_game *game, char tile, int y, int x);
void	*load_static_image(void *mlx, void *win, char **map, const char *path);
void	*load_moving_image(void *mlx, void *win, char **map, const char *path);
int		*elements_init(char **map);
int		animation_loop(t_game *game);
int		name_check(char *s);
int		map_len(char *map_file);
int		map_is_valid(char **map);
int		limits_and_elements(char **map);
int		elements_are_valid(char **map, int y);
int		is_rectangular(char **map);
int		get_map_width(char **map);
int		get_map_height(char **map);
int		get_collectables(char **map);
int		collectables_reachable(t_game game);
int		get_player_pos(char **map, int is_y);
int		get_enemy_pos(char **map, int is_y);
int		exit_reachable(t_game game);
int		close_game_return(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		animation_loop(t_game *game);
int		flood_fill(char **temp, char c, int count, int y, int x, int height, int width);

#endif
