/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:14:19 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/05 11:50:42 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemy_bounce(t_game *game, int dx, int dy)
{
	if (dx != 0)
	{
		if (game->player_y < game->enemy_y && \
			game->map[game->enemy_y - 1][game->enemy_x] == '0')
			game->enemy_y--;
		else if (game->player_y > game->enemy_y && \
			game->map[game->enemy_y + 1][game->enemy_x] == '0')
			game->enemy_y++;
	}
	else if (dy != 0)
	{
		if (game->player_x < game->enemy_x && \
			game->map[game->enemy_y][game->enemy_x - 1] == '0')
			game->enemy_x--;
		else if (game->player_x > game->enemy_x && \
			game->map[game->enemy_y][game->enemy_x + 1] == '0')
			game->enemy_x++;
	}
	return ;
}

void	enemy_movement_result(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->enemy_x + dx;
	new_y = game->enemy_y + dy;
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return ;
	tile = game->map[new_y][new_x];
	if (tile == '0' || tile == 'P')
	{
		game->enemy_x = new_x;
		game->enemy_y = new_y;
	}
	else
		enemy_bounce(game, dx, dy);
	return ;
}

void	move_enemy(t_game *game)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (game->enemy_x < game->player_x)
		dx = 1;
	else if (game->enemy_x > game->player_x)
		dx = -1;
	else if (game->enemy_y < game->player_y)
		dy = 1;
	else if (game->enemy_y > game->player_y)
		dy = -1;
	enemy_movement_result(game, dx, dy);
	if (game->enemy_x == game->player_x && game->enemy_y == game->player_y)
	{
		ft_printf("💀 GAME OVER!\n");
		exit_game(game, 0);
	}
	return ;
}

int	player_movement_result(t_game *game, int dx, int dy, char next_tile)
{
	if (next_tile == '1')
		return (0);
	if (next_tile == 'E' && game->collectable_counter > 0)
		return (0);
	if (dx == 1)
		game->last_dir = 'r';
	else if (dx == -1)
		game->last_dir = 'l';
	else if (dy == -1)
		game->last_dir = 'u';
	else if (dy == 1)
		game->last_dir = 'd';
	if (next_tile == 'C')
		game->collectable_counter --;
	if (next_tile == 'E' && game->collectable_counter == 0)
	{
		ft_printf("YOU WON!\n");
		exit_game(game, 0);
	}
	return (1);
}

void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	next_tile = game->map[new_y][new_x];
	if (!player_movement_result(game, dx, dy, next_tile))
		return ;
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	return ;
}
