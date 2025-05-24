/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:40:42 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 13:09:08 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(char **temp, char c, int count, int y, int x, int height, int width)
{
	if (count == 0)
		return (count);
	if (y < 0 || x < 0 || y >= height|| x >= width)
		return (count);
	if (temp[y][x] == 'F' || temp[y][x] != 0 && temp[y][x] != 'P' && temp[y][x] != c)
		return (count);
	if (temp[y][x] == c)
		count --;
	temp[y][x] = 'F';
	count = flood_fill(temp, c, count, y -1, x, height, width);
	count = flood_fill(temp, c, count, y +1, x, height, width);
	count = flood_fill(temp, c, count, y, x -1, height, width);
	count = flood_fill(temp, c, count, y, x +1, height, width);
	return (count);
}

char	**map_dup(t_game game)
{
	char	**map;
	char	**temp;
	int		row;

	map = game.map;
	temp = malloc(sizeof(char *) * (game.height + 1));
	if (!temp)
		return (NULL);
	row = 0;
	while (map[row])
	{
		temp[row] = ft_strdup(map[row]);
		if (temp[row] == NULL)
		{
			free_map(temp);
			return (NULL);
		}
		row++;
	}
	temp[row] = NULL;
	return (temp);
}

int	exit_reachable(t_game game)
{
	int		y;
	int		x;
	int		count;
	char	**temp;

	temp = map_dup(game);
	if (!*temp)
		return (0);
	y = game.p_y;
	x = game.p_x;
	count = 1;
	count = flood_fill(temp, 'E', count, y, x, game.height, game.width);
	free_map(temp);
	return (count == 0);
}

int	collectables_reachable(t_game game)
{
	int		y;
	int		x;
	int		count;
	char	**temp;

	temp = map_dup(game);
	if (!*temp)
		return (0);
	y = game.p_y;
	x = game.p_x;
	count = (game.c);
	count = flood_fill(temp, 'C', count, y, x, game.height, game.width);
	free_map(temp);
	return (count == 0);
}
