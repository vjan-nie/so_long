/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:36:00 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 13:09:13 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_mlx_error(void *mlx, char **map)
{
	ft_putstr_fd("MLX initialization error\n", 2);
	free_map(map);
	exit(1);
}
	
void	ft_window_error(void *mlx, void *win, char **map)
{
	ft_putstr_fd("Window creation error\n", 2);
	free_map(map);
	mlx_destroy_display(mlx);
	exit(1);
}
	