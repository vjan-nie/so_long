/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:36:17 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/04 13:56:53 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game, 0);
	else if (keycode == 'w')
		move_player(game, 0, -1);
	else if (keycode == 'a')
		move_player(game, -1, 0);
	else if (keycode == 's')
		move_player(game, 0, 1);
	else if (keycode == 'd')
		move_player(game, 1, 0);
	return (0);
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
		ft_window_error(mlx, map);
	game = game_init(mlx, win, map);
	get_frames(&game);
	enemy_init(&game);
	mlx_key_hook(win, handle_keypress, &game);
	mlx_loop_hook(mlx, animation_loop, &game);
	mlx_hook(win, 17, 0, close_game_return, &game);
	render_map(&game);
	mlx_loop(mlx);
	return ;
}
