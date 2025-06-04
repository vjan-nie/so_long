/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:42:12 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/04 14:05:33 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_width(char **map)
{
	char	*temp;
	int		width;

	temp = *map;
	width = 0;
	while (*temp)
	{
		width ++;
		temp ++;
	}
	return (width);
}

int	get_map_height(char **map)
{
	char	**temp;
	int		height;

	temp = map;
	height = 0;
	while (*temp)
	{
		height ++;
		temp ++;
	}
	return (height);
}

int	get_collectables(char **map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count ++;
			x ++;
		}
		y ++;
	}
	return (count);
}

int	get_player_pos(char **map, int is_y)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				if (is_y == 1)
					return (y);
				else
					return (x);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

int	get_enemy_pos(char **map, int is_y)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'X')
			{
				if (is_y == 1)
					return (y);
				else
					return (x);
			}
			x++;
		}
		y++;
	}
	return (-1);
}
