/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/22 14:21:13 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

/* int		name_check(char *s);
void	no_map(void);
void	too_many_args(void);
void	wrong_format(void); */
void	print_map(char **map); //early tests!
void	free_map(char **map);
char	**load_map(char *map_file);
int		len_map(char *map_file);

#endif
