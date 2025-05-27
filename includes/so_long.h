/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/27 17:24:15 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
//# include <string.h>
//# include <math.h>
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
	int		p_x;
	int		p_y;
	int		c;
	int		moves;

	void	*img_wall;
	void	*img_background;

	void	*img_p;
	void	*img_c;
	void	*img_e;
	void	*img_enemy;

	void	*player_down[4];
	void	*player_up[4];
	void	*player_left[4];
	void	*player_right[4];

	void	*collectable[3];
	void	*exit[2];

	int		player_index;
	int		collectable_index;
	int		exit_index;

	int		frame_counter;
	int		collectable_counter;
	int		exit_counter;

	char	last_dir;

	int		enemy_x;
	int		enemy_y;
	int		enemy_dx; // dirección en x (1 o -1)
	int		enemy_dy; // dirección en y (1 o -1)
	int		enemy_timer;
}			t_game;

void	so_long(void *mlx, char **map);
void	arg_check(int argc, char **argv);
void	arg_error(char *error);
void	map_error(char *error);
void	ft_mlx_error(char **map);
void	ft_window_error(void *mlx, char **map);
void	free_map(char **map);
void	render_map(t_game *game);
t_game	game_init(void *mlx, void *win, char **map);
char	**load_map(char *map_file);
int	animation_loop(t_game *game);
int		name_check(char *s);
int		len_map(char *map_file);
int		map_valid(char **map);
int	get_map_width(char **map);
int	get_map_height(char **map);
int	collectables_reachable(t_game game);
int		get_player_pos(char **map, int is_y);
int	exit_reachable(t_game game);
char	**map_dup(t_game game);
int	handle_close(t_game *game);
void	exit_game(t_game *game);
int	handle_keypress(int keycode, t_game *game);
int	animation_loop(t_game *game);
void	move_enemy(t_game *game);
void	move_player(t_game *game, int dx, int dy);
int	flood_fill(char **temp, char c, int count, int y, int x, int height, int width);

#endif
