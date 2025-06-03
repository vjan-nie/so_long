/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:30:21 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:21 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_len(char *map_file)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

int	flood_fill(char **temp, char c, int count, int y, int x, int height, int width)
{
	if (count == 0)
		return (count);
	if (y < 0 || x < 0 || y >= height|| x >= width)
		return (count);
	if ((temp[y][x] == 'F' || temp[y][x] != 0) \
	&& temp[y][x] != 'P' && temp[y][x] != c)
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
