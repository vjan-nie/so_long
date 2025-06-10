/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:54 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/10 11:48:20 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*safe_load_image(t_game *game, const char *path, int moving)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(game->mlx, (char *)path, &w, &h);
	if (!img)
	{
		if (moving)
			free((char *)path);
		ft_img_error(game);
	}
	return (img);
}

char	*image_path(const char *prefix, int index, const char *suffix)
{
	char	*number;
	char	*temp;
	char	*result;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	temp = ft_strjoin(prefix, number);
	free(number);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

void	get_player_frames(t_game *game)
{
	char	*path;
	int		i;

	i = 0;
	while (i < 4)
	{
		path = image_path("images/P_down", i + 1, ".xpm");
		game->player_down[i] = safe_load_image(game, path, 1);
		free(path);
		path = image_path("images/P_up", i + 1, ".xpm");
		game->player_up[i] = safe_load_image(game, path, 1);
		free(path);
		path = image_path("images/P_left", i + 1, ".xpm");
		game->player_left[i] = safe_load_image(game, path, 1);
		free(path);
		path = image_path("images/P_right", i + 1, ".xpm");
		game->player_right[i] = safe_load_image(game, path, 1);
		free(path);
		i ++;
	}
	return ;
}

void	get_static_frames(t_game *game)
{
	game->img_wall = safe_load_image(game, "images/wall2.xpm", 0);
	game->img_background = safe_load_image(game, "images/background.xpm", 0);
	if (game->enemy_x != -1 && game->enemy_y != -1)
		game->img_enemy = safe_load_image(game, "images/enemy.xpm", 0);
}

void	get_frames(t_game *game)
{
	char	*path;
	int		i;

	get_static_frames(game);
	get_player_frames(game);
	i = 0;
	while (i < 3)
	{
		path = image_path("images/C", i + 1, ".xpm");
		game->collectable[i] = safe_load_image(game, path, 1);
		free(path);
		i ++;
	}
	i = 0;
	while (i < 2)
	{
		path = image_path("images/E", i + 1, ".xpm");
		game->exit[i] = safe_load_image(game, path, 1);
		free(path);
		i ++;
	}
	return ;
}
