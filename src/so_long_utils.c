/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:19 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/27 17:40:19 by vjan-nie         ###   ########.fr       */
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

int	handle_close(t_game *game)
{
	exit_game(game);
	return (0);
}

void	exit_game(t_game *game)
{
	// Libera imágenes del jugador
	for (int i = 0; i < 4; i++)
	{
		mlx_destroy_image(game->mlx, game->player_down[i]);
		mlx_destroy_image(game->mlx, game->player_up[i]);
		mlx_destroy_image(game->mlx, game->player_left[i]);
		mlx_destroy_image(game->mlx, game->player_right[i]);
	}

	// Libera animaciones coleccionables y salida
	for (int i = 0; i < 3; i++)
		mlx_destroy_image(game->mlx, game->collectable[i]);
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(game->mlx, game->exit[i]);

	// Libera imágenes estáticas
	mlx_destroy_image(game->mlx, game->img_wall);
	mlx_destroy_image(game->mlx, game->img_background);

	// Cierra ventana
	mlx_destroy_window(game->mlx, game->win);

	// Libera mapa
	free_map(game->map); // asegúrate de tener esta función

	exit(0);
}

t_game	game_init(void *mlx, void *win, char **map)
{
	t_game	game;
	int		y, x, w, h;
	char	path[64];

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
	game.enemy_x = 1;
	game.enemy_y = 1;
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
	game.img_enemy = mlx_xpm_file_to_image(mlx, "images/enemy.xpm", &w, &h);
	// Cargar animaciones jugador
	for (int i = 0; i < 4; i++)
	{
		snprintf(path, sizeof(path), "images/P_down%d.xpm", i + 1);
		game.player_down[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
		snprintf(path, sizeof(path), "images/P_up%d.xpm", i + 1);
		game.player_up[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
		snprintf(path, sizeof(path), "images/P_left%d.xpm", i + 1);
		game.player_left[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
		snprintf(path, sizeof(path), "images/P_right%d.xpm", i + 1);
		game.player_right[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
	}

	// Cargar animaciones coleccionables
	for (int i = 0; i < 3; i++)
	{
		snprintf(path, sizeof(path), "images/C%d.xpm", i + 1);
		game.collectable[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
	}

	// Cargar animaciones salida
	for (int i = 0; i < 2; i++)
	{
		snprintf(path, sizeof(path), "images/E%d.xpm", i + 1);
		game.exit[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
	}

	return (game);
}
