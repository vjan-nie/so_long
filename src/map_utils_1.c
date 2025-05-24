/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:30:21 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 13:09:10 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	len_map(char *map_file)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (0);
	rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		rows++;
	}
	close(fd);
	return (rows);
}

void free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

char	**load_map(char *map_file)
{
	int		fd;
	char	*line;
	char	*clean_line;
	char	**map;
	int		rows;
	int		row;

	rows = len_map(map_file);
	if (rows == 0)
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	row = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		clean_line = ft_strtrim(line, "\n");
		free(line);
		if (!clean_line)
		{
			free_map(map);
			close(fd);
			return (NULL);
		}
		map[row] = clean_line;
		line = get_next_line(fd);
		row++;
	}
	map[row] = NULL;
	close(fd);
	return (map);
}

int	map_valid(char **map)
{
	size_t	width;
	int		y;
	int		x;
	int		p;
	int		e;
	int		c;

	y = 0;
	width = ft_strlen(map[0]);
	p = 0;
	e = 0;
	c = 0;
	while (map[y])
	{
		if (ft_strlen(map[y]) != width)
			return (0);
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("01PCE\n", map[y][x]))
				return(0);
			if (((y == 0 || !map[y + 1]) || x == 0 || x == (int)width - 1)\
			&& map[y][x] != '1')
				return (0);
			if (map[y][x] == 'P')
				p++;
			if (map[y][x] == 'E')
				e++;
			if (map[y][x] == 'C')
				c++;
			x ++;
		}
		y++;
	}
	if (p != 1 || e != 1 || c < 1)
		return (0);
	return (1);
}
