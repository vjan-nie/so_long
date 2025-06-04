/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:34:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:38 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemy_init(t_game *game)
{
	game->enemy_x = get_enemy_pos(game->map, 0);
	if (game->enemy_x == -1)
		game->enemy_y = -1;
	else
		game->enemy_y = get_enemy_pos(game->map, 1);
	game->enemy_dx = 1;
	game->enemy_dy = 0;
	game->enemy_timer = 0;
	return ;
}

t_game	game_init(void *mlx, void *win, char **map)
{
	t_game	game;

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
	return (game);
}
