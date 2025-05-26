/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/26 13:21:35 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
//# include <string.h>
//# include <math.h>
# include <mlx.h>
# include "libft.h"

# define TILE_SIZE 64

typedef struct s_game
{
	void	*mlx;        // puntero al contexto de MLX
	void	*win;        // puntero a la ventana
	char	**map;       // mapa cargado
	int		width;      // ancho del mapa (en tiles)
	int		height;     // alto del mapa (en tiles)
	int		p_x;   // posición del jugador (columna)
	int		p_y;   // posición del jugador (fila)
	int		c;   // total de coleccionables restantes
	int		moves;      // cantidad de movimientos hechos
	// sprites
	void	*img_wall;
	void	*img_background;
	void	*img_p;
	void	*img_e;
	void	*img_c;
}			t_game;

void	so_long(void *mlx, char **map);
void	arg_check(int argc, char **argv);
void	arg_error(char *error);
void	map_error(char *error);
void	ft_mlx_error(char **map);
void	ft_window_error(void *mlx, char **map);
void	free_map(char **map);
void	render_map(t_game *game);
t_game	game_init(void *mlx, void *win, char **map);
char	**load_map(char *map_file);
int		name_check(char *s);
int		len_map(char *map_file);
int		map_valid(char **map);
int	get_map_width(char **map);
int	get_map_height(char **map);
int	collectables_reachable(t_game game);
int		get_player_pos(char **map, int is_y);
int	exit_reachable(t_game game);
char	**map_dup(t_game game);
int	flood_fill(char **temp, char c, int count, int y, int x, int height, int width);

#endif
