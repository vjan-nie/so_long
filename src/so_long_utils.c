/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:19 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/28 14:29:01 by vjan-nie         ###   ########.fr       */
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

int	handle_close(t_game *game)
{
	exit_game(game);
	return (0);
}

void	exit_game(t_game *game)
{
	if (game->mlx)
	{
		for (int i = 0; i < 4; i++)
		{
			if (game->player_down[i])
				mlx_destroy_image(game->mlx, game->player_down[i]);
			if (game->player_up[i])
				mlx_destroy_image(game->mlx, game->player_up[i]);
			if (game->player_left[i])
				mlx_destroy_image(game->mlx, game->player_left[i]);
			if (game->player_right[i])
				mlx_destroy_image(game->mlx, game->player_right[i]);
		}

		for (int i = 0; i < 3; i++)
		{
			if (game->collectable[i])
				mlx_destroy_image(game->mlx, game->collectable[i]);
		}

		for (int i = 0; i < 2; i++)
		{
			if (game->exit[i])
				mlx_destroy_image(game->mlx, game->exit[i]);
		}

		if (game->img_wall)
			mlx_destroy_image(game->mlx, game->img_wall);
		if (game->img_background)
			mlx_destroy_image(game->mlx, game->img_background);
		if (game->img_enemy)
    		mlx_destroy_image(game->mlx, game->img_enemy);

		if (game->win)
			mlx_destroy_window(game->mlx, game->win);

		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

	if (game->map)
		free_map(game->map);

	exit(0);
}

void	*safe_load_image(void *mlx, const char *path, int *w, int *h)
{
	void *img = mlx_xpm_file_to_image(mlx, (char *)path, w, h);
	if (!img)
	{
		ft_putstr_fd("Load image error\n", 2);
		exit(1);
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

t_game	game_init(void *mlx, void *win, char **map)
{
	t_game	game;
	int		y, x, w, h;
	char	*path;

	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx;
	game.win = win;
	game.map = map;
	game.width = get_map_width(map);
	game.height = get_map_height(map);
	game.c = 0;
	game.moves = 0;
	game.p_x = get_player_pos(map, 0);
	game.p_y = get_player_pos(map, 1);
	game.frame_counter = 0;
	game.collectable_counter = 0;
	game.exit_counter = 0;
	game.player_index = 0;
	game.collectable_index = 0;
	game.exit_index = 0;
	game.last_dir = 'd';
	game.enemy_x = get_enemy_pos(map, 0);
	game.enemy_y = get_enemy_pos(map, 1);
	game.enemy_dx = 1;
	game.enemy_dy = 0;
	game.enemy_timer = 0;

	// Contar coleccionables y encontrar posición de jugador
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
			{
				game.p_y = y;
				game.p_x = x;
			}
			else if (map[y][x] == 'C')
				game.c++;
		}
	}

	// Cargar imágenes estáticas
	game.img_wall = mlx_xpm_file_to_image(mlx, "images/wall2.xpm", &w, &h);
	game.img_background = mlx_xpm_file_to_image(mlx, "images/background.xpm", &w, &h);
	if (game.enemy_x != -1 && game.enemy_y != -1)
		game.img_enemy = mlx_xpm_file_to_image(mlx, "images/enemy.xpm", &w, &h);
	// Cargar animaciones jugador
	for (int i = 0; i < 4; i++)
	{
		path = image_path("images/P_down", i + 1, ".xpm");
		game.player_down[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
		path = image_path("images/P_up", i + 1, ".xpm");
		game.player_up[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
		path = image_path("images/P_left", i + 1, ".xpm");
		game.player_left[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
		path = image_path("images/P_right", i + 1, ".xpm");
		game.player_right[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
	}

	// Cargar animaciones coleccionables
	for (int i = 0; i < 3; i++)
	{
		path = image_path("images/C", i + 1, ".xpm");
		game.collectable[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
	}

	// Cargar animaciones salida
	for (int i = 0; i < 2; i++)
	{
		path = image_path("images/E", i + 1, ".xpm");
		game.exit[i] = safe_load_image(mlx, path, &w, &h);
		free(path);
	}

	return (game);
}
