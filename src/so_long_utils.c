/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:19 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 13:18:09 by vjan-nie         ###   ########.fr       */
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

t_game	game_init(void *mlx, void *win, char **map)
{
	t_game	game;
	int		y;
	int		x;

	game.mlx = mlx;
	game.win = win;
	game.map = map;
	game.width = get_map_width(map);
	game.height = get_map_height(map);
	game.c = 0;
	game.moves = 0;
	game.p_x = get_player_pos(map, 0);
	game.p_y = get_player_pos(map, 1);

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				game.p_y = y;
				game.p_x = x;
			}
			else if (map[y][x] == 'C')
				game.c++;
			x++;
		}
		y++;
	}
	// cargar sprites:
	int	w, h;
	game.img_wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &w, &h);
	game.img_background = mlx_xpm_file_to_image(mlx, "textures/ground.xpm", &w, &h);
	game.img_p = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &w, &h);
	game.img_c = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &w, &h);
	game.img_e = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &w, &h);
	return (game);
}
