/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:09 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/11 12:41:35 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*draw_player(t_game *game)
{
	if (game->last_dir == 'u')
		return (game->player_up[game->player_index]);
	else if (game->last_dir == 'd')
		return (game->player_down[game->player_index]);
	else if (game->last_dir == 'l')
		return (game->player_left[game->player_index]);
	else if (game->last_dir == 'r')
		return (game->player_right[game->player_index]);
	else
		return (game->player_down[0]);
	return (NULL);
}

void	draw_tile(t_game *game, int y, int x)
{
	void	*img;
	char	tile;

	tile = game->map[y][x];
	mlx_put_image_to_window(game->mlx, game->win, \
	game->img_background, x * TILE_SIZE, y * TILE_SIZE);
	if (tile == '1')
		img = game->img_wall;
	else if (tile == 'P')
		img = draw_player(game);
	else if (tile == 'C')
		img = game->collectable[game->collectable_index];
	else if (tile == 'E')
		img = game->exit[game->exit_index];
	else
		img = NULL;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win,
			img, x * TILE_SIZE, y * TILE_SIZE);
	return ;
}

void	render_map(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, y, x);
			x++;
		}
		y++;
	}
	if (game->enemy_x != -1)
	{
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img_enemy, game->enemy_x * TILE_SIZE, game->enemy_y * TILE_SIZE);
	}
	return ;
}

void	enemy_ready(t_game *game)
{
	game->enemy_timer++;
	if (game->enemy_timer >= 400)
	{
		game->enemy_timer = 0;
		move_enemy(game);
	}
	return ;
}

int	animation_loop(t_game *game)
{
	game->player_timer++;
	game->collectable_timer++;
	game->exit_timer++;
	if (game->player_timer >= 120)
	{
		game->player_timer = 0;
		game->player_index = (game->player_index + 1) % 4;
	}
	if (game->collectable_timer >= 200)
	{
		game->collectable_timer = 0;
		game->collectable_index = (game->collectable_index + 1) % 3;
	}
	if (game->exit_timer >= 300)
	{
		game->exit_timer = 0;
		game->exit_index = (game->exit_index + 1) % 2;
	}
	if (game->enemy_x != -1)
		enemy_ready(game);
	render_map(game);
	return (0);
}
