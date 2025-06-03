/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:19 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/03 16:54:40 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_width(char **map)
{
	char	*temp;
	int		width;

	temp = *map;
	width = 0;
	while (*temp)
	{
		width ++;
		temp ++;
	}
	return (width);
}

int	get_map_height(char **map)
{
	char	**temp;
	int		height;

	temp = map;
	height = 0;
	while (*temp)
	{
		height ++;
		temp ++;
	}
	return (height);
}

int		get_player_pos(char **map, int is_y)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				if (is_y == 1)
					return (y);
				else
					return (x);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

int		get_enemy_pos(char **map, int is_y)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'X')
			{
				if (is_y == 1)
					return (y);
				else
					return (x);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

void	*load_static_image(void *mlx, void *win, char **map, const char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
		ft_img_error(mlx, win, map);
	return (img);
}

void	*load_moving_image(void *mlx, void *win, char **map, const char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
	{
		free(path);
		ft_img_error(mlx, win, map);
	}
	return (img);
}

char	*image_path(const char *prefix, int index, const char *suffix)
{
	char	*number;
	char	*temp;
	char	*result;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	temp = ft_strjoin(prefix, number);
	free(number);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

int	get_collectables(char **map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count ++;
			x ++;
		}
		y ++;
	}
	return (count);
}

t_game	game_init(void *mlx, void *win, char **map)
{
	t_game	game;
	char	*path;

	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx;
	game.win = win;
	game.map = map;
	game.width = get_map_width(map);
	game.height = get_map_height(map);
	game.collectable_index = 0;
	game.moves = 0;
	game.player_x = get_player_pos(map, 0);
	game.player_y = get_player_pos(map, 1);
	game.player_timer = 0;
	game.collectable_counter = get_collectables(map);
	game.collectable_timer = 0;
	game.exit_timer = 0;
	game.player_index = 0;
	game.exit_index = 0;
	game.last_dir = 'd';
	game.enemy_x = get_enemy_pos(map, 0);
	if (game.enemy_x == -1)
		game.enemy_y = -1;
	else
		game.enemy_y = get_enemy_pos(map, 1);
	game.enemy_dx = 1;
	game.enemy_dy = 0;
	game.enemy_timer = 0;

	// wall, background & enemy
	game.img_wall = load_static_image(mlx, win, map, "images/wall2.xpm");
	game.img_background = load_static_image(mlx, win, map, "images/background.xpm");
	if (game.enemy_x != -1 && game.enemy_y != -1)
		game.img_enemy = load_static_image(mlx, win, map, "images/enemy.xpm");
	// player animation
	for (int i = 0; i < 4; i++)
	{
		path = image_path("images/P_down", i + 1, ".xpm");
		game.player_down[i] = load_moving_image(mlx, win, map, path);
		free(path);
		path = image_path("images/P_up", i + 1, ".xpm");
		game.player_up[i] = load_moving_image(mlx, win, map, path);
		free(path);
		path = image_path("images/P_left", i + 1, ".xpm");
		game.player_left[i] = load_moving_image(mlx, win, map, path);
		free(path);
		path = image_path("images/P_right", i + 1, ".xpm");
		game.player_right[i] = load_moving_image(mlx, win, map, path);
		free(path);
	}

	// Cs animation
	for (int i = 0; i < 3; i++)
	{
		path = image_path("images/C", i + 1, ".xpm");
		game.collectable[i] = load_moving_image(mlx, win, map, path);
		free(path);
	}

	// exit animation
	for (int i = 0; i < 2; i++)
	{
		path = image_path("images/E", i + 1, ".xpm");
		game.exit[i] = load_moving_image(mlx, win, map, path);
		free(path);
	}

	return (game);
}
