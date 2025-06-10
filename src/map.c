/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:04:50 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/10 16:29:09 by vjan-nie         ###   ########.fr       */
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

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

int	map_is_valid(char **map)
{
	int	y;

	y = 0;
	if (get_map_width(map) < 1)
		return (0);
	if (!is_rectangular(map))
		return (0);
	if (!limits_and_elements(map))
		return (0);
	if (!elements_are_valid(map, y))
		return (0);
	if (!collectables_reachable(map))
		return (0);
	if (!exit_reachable(map))
		return (0);
	return (1);
}

char	**get_map(char **map, int fd) //Read and safe in array
{
	char	*line;
	char	*clean_line;
	int		row;

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

char	**load_map(char *map_file) //Prepare
{
	int		fd;
	char	**map;
	int		rows;

	rows = map_len(map_file);
	if (rows < 1)
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
	map = get_map(map, fd);
	return (map);
}
