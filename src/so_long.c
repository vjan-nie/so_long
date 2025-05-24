/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:36:17 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 13:19:38 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	render_map(t_game *game)
{
	int	x, y;
	void	*img;
	char	tile;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			tile = game->map[y][x];

			// fondo primero (por debajo de todo)
			mlx_put_image_to_window(game->mlx, game->win,
				game->img_background, x * TILE_SIZE, y * TILE_SIZE);

			if (tile == '1')
				img = game->img_wall;
			else if (tile == 'P')
				img = game->img_p;
			else if (tile == 'C')
				img = game->img_c;
			else if (tile == 'E')
				img = game->img_e;
			else
				img = NULL;

			if (img)
				mlx_put_image_to_window(game->mlx, game->win,
					img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	so_long(void *mlx, char **map)
{
	t_game	game;
	void	*win;
	int		width;
	int		height;

	width = get_map_width(map) * TILE_SIZE;
	height = get_map_height(map) * TILE_SIZE;
	win = mlx_new_window(mlx, width, height, "so_long");
	if (!win)
		window_error(mlx, win, map);
	game = game_init(mlx, win, map);

	
	render_map(&game);
	// Aquí deberían venir hooks, render inicial, etc.
	// ej: render_map(game);
	//     mlx_key_hook(win, key_handler, &game);
	mlx_loop(mlx);
	return ;
}
