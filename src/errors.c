/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:03:52 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/10 11:45:44 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	arg_error(char *error) //Errors in user's call: messange in terminal
{
	ft_printf("Error\n");
	ft_printf("%s", error);
	exit(1);
}

void	map_error(char **map, char *error)
{
	if (map)
		free_map(map);
	ft_printf("Error\n");
	ft_putstr_fd(error, 2);
	exit(1);
}

void	ft_mlx_error(char **map)
{
	ft_printf("Error\n");
	ft_putstr_fd("MLX initialization error\n", 2);
	free_map(map);
	exit(1);
}

void	ft_window_error(void *mlx, char **map)
{
	ft_printf("Error\n");
	ft_putstr_fd("Window creation error\n", 2);
	free_map(map);
	mlx_destroy_display(mlx);
	exit(1);
}

void	ft_img_error(t_game *game)
{
	ft_printf("Error\n");
	ft_putstr_fd("Load image error\n", 2);
	exit_game(game, 1);
	exit(1);
}
