/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:36:17 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/03 16:03:00 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player(t_game *game, void *img)
{
	if (game->last_dir == 'u')
		img = game->player_up[game->player_index];
	else if (game->last_dir == 'd')
		img = game->player_down[game->player_index];
	else if (game->last_dir == 'l')
		img = game->player_left[game->player_index];
	else if (game->last_dir == 'r')
		img = game->player_right[game->player_index];
	else
		img = game->player_down[0];
	return ;
}

void	draw_tile(t_game *game, char tile, int y, int x)
{
	void	*img;

	tile = game->map[y][x];
	mlx_put_image_to_window(game->mlx, game->win, \
	game->img_background, x * TILE_SIZE, y * TILE_SIZE);
	if (tile == '1')
		img = game->img_wall;
	else if (tile == 'P')
		draw_player(game, img);
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
	void	*img;
	char	tile;
	int		x;
	int		y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, tile, y, x);
			x++;
		}
		y++;
	}
	if (game->enemy_x != -1)
	{
		mlx_put_image_to_window(game->mlx, game->win,\
		game->img_enemy, game->enemy_x * TILE_SIZE, game->enemy_y * TILE_SIZE);
	}
	return ;
}

void	enemy_animation(t_game *game)
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
	if (game->collectable_counter >= 200)
	{
		game->collectable_counter = 0;
		game->collectable_index = (game->collectable_index + 1) % 3;
	}
	if (game->exit_timer >= 300)
	{
		game->exit_timer = 0;
		game->exit_index = (game->exit_index + 1) % 2;
	}
	if (game->enemy_x != -1)
		enemy_animation(game);
	render_map(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
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

void	enemy_bounce(t_game *game, int dx, int dy)
{
	if (dx != 0) 
	{
		if (game->player_y < game->enemy_y &&
			game->map[game->enemy_y - 1][game->enemy_x] == '0')
			game->enemy_y--;
		else if (game->player_y > game->enemy_y &&
			game->map[game->enemy_y + 1][game->enemy_x] == '0')
			game->enemy_y++;
	}
	else if (dy != 0)
	{
		if (game->player_x < game->enemy_x &&
			game->map[game->enemy_y][game->enemy_x - 1] == '0')
			game->enemy_x--;
		else if (game->player_x > game->enemy_x &&
			game->map[game->enemy_y][game->enemy_x + 1] == '0')
			game->enemy_x++;
	}
	return ;
}

void	enemy_movement_result(t_game *game, int dx, int dy, char tile)
{
	char	tile;
	int		new_x;
	int		new_y;

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
	int 	dx;
	int 	dy;
	char	tile;

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
	enemy_movement_result(game, dx, dy, tile);
	if (game->enemy_x == game->player_x && game->enemy_y == game->player_y)
	{
		ft_printf("💀 GAME OVER!\n");
		exit_game(game);
	}
	return ;
}

void	player_movement_result(t_game *game, int dx, int dy, char next_tile)
{
	if (next_tile == '1')
		return ;
	if (next_tile == 'E' && game->collectable_counter > 0)
		return ;
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
		exit_game(game);
	}
	return ;
}

void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	next_tile = game->map[new_y][new_x];
	player_movement_result(game, dx, dy, next_tile);
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	return ;
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
	mlx_key_hook(win, handle_keypress, &game);
	mlx_loop_hook(mlx, animation_loop, &game);
	mlx_hook(win, 17, 0, close_game_return, &game);
	render_map(&game);
	mlx_loop(mlx);
	return ;
}
