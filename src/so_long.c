/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:36:17 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/28 12:55:08 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_game *game)
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
					img = game->player_down[0]; // por defecto
			}
			else if (tile == 'C')
				img = game->collectable[game->collectable_index];
			else if (tile == 'E')
				img = game->exit[game->exit_index];
			else
				img = NULL;

			if (img)
				mlx_put_image_to_window(game->mlx, game->win,
					img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	if (game->enemy_x != -1 && game->enemy_y != -1)
	{
		mlx_put_image_to_window(game->mlx, game->win,\
		game->img_enemy, game->enemy_x * TILE_SIZE, game->enemy_y * TILE_SIZE);
	}
	char *str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 20, 50, 0xFF00FF, str);
	free(str);
}

int	animation_loop(t_game *game)
{
	game->frame_counter++;
	game->collectable_counter++;
	game->exit_counter++;

	// Jugador: cada 6 ciclos (~100ms si tu loop va a ~60fps)
	if (game->frame_counter >= 120)
	{
		game->frame_counter = 0;
		game->player_index = (game->player_index + 1) % 4;
	}

	// Coleccionables: cada 15 ciclos (~250ms)
	if (game->collectable_counter >= 200)
	{
		game->collectable_counter = 0;
		game->collectable_index = (game->collectable_index + 1) % 3;
	}

	// Salida: cada 30 ciclos (~500ms)
	if (game->exit_counter >= 300)
	{
		game->exit_counter = 0;
		game->exit_index = (game->exit_index + 1) % 2;
	}
	if (game->enemy_x != -1 && game->enemy_y != -1)
	{
		game->enemy_timer++;
		if (game->enemy_timer >= 400) // mueve cada 10 ciclos
		{
			game->enemy_timer = 0;
			move_enemy(game);
		}
	}
	render_map(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC
		exit_game(game); // una función que libere recursos y cierre

	// Movimiento: W A S D
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

void	move_enemy(t_game *game)
{
	int dx = 0;
	int dy = 0;

	// Dirección principal hacia el jugador
	if (game->enemy_x < game->p_x)
		dx = 1;
	else if (game->enemy_x > game->p_x)
		dx = -1;
	else if (game->enemy_y < game->p_y)
		dy = 1;
	else if (game->enemy_y > game->p_y)
		dy = -1;

	int new_x = game->enemy_x + dx;
	int new_y = game->enemy_y + dy;

	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return;
	char tile = game->map[new_y][new_x];

	if (tile == '0' || tile == 'P')
	{
		game->enemy_x = new_x;
		game->enemy_y = new_y;
	}
	else
	{
		// Rebote: intenta moverse en perpendicular
		if (dx != 0) // intentaba moverse en X
		{
			if (game->p_y < game->enemy_y &&
				game->map[game->enemy_y - 1][game->enemy_x] == '0')
				game->enemy_y--;
			else if (game->p_y > game->enemy_y &&
				game->map[game->enemy_y + 1][game->enemy_x] == '0')
				game->enemy_y++;
		}
		else if (dy != 0) // intentaba moverse en Y
		{
			if (game->p_x < game->enemy_x &&
				game->map[game->enemy_y][game->enemy_x - 1] == '0')
				game->enemy_x--;
			else if (game->p_x > game->enemy_x &&
				game->map[game->enemy_y][game->enemy_x + 1] == '0')
				game->enemy_x++;
		}
	}

	// Verifica colisión con el jugador
	if (game->enemy_x == game->p_x && game->enemy_y == game->p_y)
	{
		ft_printf("💀 GAME OVER!\n");
		exit_game(game);
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x = game->p_x + dx;
	int	new_y = game->p_y + dy;
	char	next_tile = game->map[new_y][new_x];

	// Si es muro, no se puede pasar
	if (next_tile == '1')
		return;

	// Si es salida y aún quedan coleccionables, no se puede pasar
	if (next_tile == 'E' && game->c > 0)
		return;

	// Actualizar dirección del jugador
	if (dx == 1)
		game->last_dir = 'r';
	else if (dx == -1)
		game->last_dir = 'l';
	else if (dy == -1)
		game->last_dir = 'u';
	else if (dy == 1)
		game->last_dir = 'd';

	// Si es coleccionable, disminuir contador
	if (next_tile == 'C')
		game->c--;

	// Si es salida y ya no quedan coleccionables, gana el juego
	if (next_tile == 'E' && game->c == 0)
	{
		ft_printf("YOU WON!\n");
		exit_game(game);
	}

	// Mover jugador (no reemplazar la salida con '0')
	// Para que no se borre la 'E', solo reemplazamos el 'P' anterior con '0'
	game->map[game->p_y][game->p_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->p_x = new_x;
	game->p_y = new_y;
	game->moves++;

	ft_printf("Movimientos: %d\n", game->moves);
	render_map(game);
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
	mlx_hook(win, 17, 0, handle_close, &game); // Cierre ventana

	render_map(&game); // Primer render
	mlx_loop(mlx);
}
