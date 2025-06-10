/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:40:42 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/10 16:26:57 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_reachable(char **map)
{
	int		y;
	int		x;
	int		count;
	char	**temp;

	temp = map_dup(map);
	if (!temp)
		return (0);
	y = get_player_pos(map, 1);
	x = get_player_pos(map, 0);
	count = 1;
	count = flood_fill_exit(temp, count, y, x);
	free_map(temp);
	return (count == 0);
}

int	collectables_reachable(char **map)
{
	int		y;
	int		x;
	int		count;
	char	**temp;

	temp = map_dup(map);
	if (!temp)
		return (0);
	y = get_player_pos(map, 1);
	x = get_player_pos(map, 0);
	count = get_collectables(map);
	count = flood_fill_collect(temp, count, y, x);
	free_map(temp);
	return (count == 0);
}

int	is_rectangular(char **map)
{
	size_t	width;
	int		y;

	if (!map || !map[0])
		return (0);
	y = 0;
	width = ft_strlen(map[0]);
	while (map[y])
	{
		if (ft_strlen(map[y]) != width)
			return (0);
		y ++;
	}
	return (1);
}

int	limits_and_elements(char **map)
{
	size_t	width;
	int		x;
	int		y;

	width = ft_strlen(map[0]);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("01PCEX\n", map[y][x]))
				return (0);
			if (((y == 0 || !map[y + 1]) || x == 0 || x == (int)width - 1) \
			&& map[y][x] != '1')
				return (0);
			x ++;
		}
		y++;
	}
	return (1);
}

int	elements_are_valid(char **map, int y)
//elements[]: 0 - player / 1 - exit / 2 - collectible / 3 - enemy
{
	int		*elements;
	int		x;

	elements = elements_init(map);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				elements[0]++;
			if (map[y][x] == 'E')
				elements[1]++;
			if (map[y][x] == 'C')
				elements[2]++;
			if (map[y][x] == 'X')
				elements[3]++;
			x ++;
		}
		y++;
	}
	if (elements[0] != 1 || elements[1] != 1 \
	|| elements[2] < 1 || elements[3] > 1)
		return (free_elements(elements), 0);
	return (free_elements(elements), 1);
}
