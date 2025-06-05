/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:30:21 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/05 11:37:03 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill_collect(char **temp, int count, int y, int x)
{
	if (count == 0)
		return (count);
	if (y < 0 || x < 0 || !temp[y] || temp[y][x] == '\0')
		return (count);
	if ((temp[y][x] == 'F' || temp[y][x] != 0) \
	&& temp[y][x] != 'P' && temp[y][x] != 'C')
		return (count);
	if (temp[y][x] == 'C')
		count --;
	temp[y][x] = 'F';
	count = flood_fill_collect(temp, count, y -1, x);
	count = flood_fill_collect(temp, count, y +1, x);
	count = flood_fill_collect(temp, count, y, x -1);
	count = flood_fill_collect(temp, count, y, x +1);
	return (count);
}

int	flood_fill_exit(char **temp, int count, int y, int x)
{
	if (count == 0)
		return (count);
	if (y < 0 || x < 0 || !temp[y] || temp[y][x] == '\0')
		return (count);
	if ((temp[y][x] == 'F' || temp[y][x] != 0) \
	&& temp[y][x] != 'P' && temp[y][x] != 'E')
		return (count);
	if (temp[y][x] == 'E')
		count --;
	temp[y][x] = 'F';
	count = flood_fill_exit(temp, count, y -1, x);
	count = flood_fill_exit(temp, count, y +1, x);
	count = flood_fill_exit(temp, count, y, x -1);
	count = flood_fill_exit(temp, count, y, x +1);
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

int	*elements_init(char **map)
{
	int	i;
	int	*elements;

	elements = malloc(sizeof(int) * 4);
	if (!elements)
		map_error(map, "Malloc to init elements failed\n");
	i = 0;
	while (i < 4)
	{
		elements[i] = 0;
		i ++;
	}
	return (elements);
}

void	free_elements(int *elements)
{
	if (!elements)
		return ;
	free(elements);
	return ;
}
