/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:30:21 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/22 14:36:08 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* int	name_check(char *s)
{
	int	len;
	
	len = ft_strlen(s) - 1;
	while (len > 0 && s[len] != '.')
		len --;
	if (len != 0 && ft_strncmp(s[len], ".ber", 4) == 0)
		return (1);
	return (0);
}
 */

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
		map[row] = ft_strdup(line);
		free(line);
		if (map[row] == NULL)
		{
			free_map(map);
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
		row++;
	}
	map[row] = NULL;
	close(fd);
	return (map);
}

void	print_map(char **map) //early tests
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("%s", map[i]);
		i++;
	}
	return ;
}
