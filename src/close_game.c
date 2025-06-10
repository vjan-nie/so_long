/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:08:50 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/10 15:57:53 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game_return(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

void	clear_player_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->player_down[i])
			mlx_destroy_image(game->mlx, game->player_down[i]);
		if (game->player_up[i])
			mlx_destroy_image(game->mlx, game->player_up[i]);
		if (game->player_left[i])
			mlx_destroy_image(game->mlx, game->player_left[i]);
		if (game->player_right[i])
			mlx_destroy_image(game->mlx, game->player_right[i]);
		i ++;
	}
	return ;
}

void	clear_c_and_e_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->collectable[i])
			mlx_destroy_image(game->mlx, game->collectable[i]);
		i ++;
	}
	i = 0;
	while (i < 2)
	{
		if (game->exit[i])
			mlx_destroy_image(game->mlx, game->exit[i]);
		i ++;
	}
	return ;
}

void	clear_static_images(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_background)
		mlx_destroy_image(game->mlx, game->img_background);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	return ;
}

void	exit_game(t_game *game, int error)
{
	if (game->mlx)
	{
		clear_player_images(game);
		clear_c_and_e_images(game);
		clear_static_images(game);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	if (error)
		exit(1);
	exit(0);
}
