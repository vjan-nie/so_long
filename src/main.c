/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:53 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:50 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

int	main(void)
{
	void	*mlx;
	void	*win;
	char	**map;

	map = load_map("maps/map_test1.ber");
	if (map == NULL)
	{
		ft_putstr_fd("Map load error\n", 2);
		return (1);
	}
	print_map(map);
	mlx = mlx_init();
	if (!mlx)
	{
		ft_putstr_fd("MLX initialization error\n", 2);
		free_map(map);
		return (1);
	}
	win = mlx_new_window(mlx, 800, 600, "so_long");
	if (!win)
	{
		ft_putstr_fd("Window creation error\n", 2);
		free_map(map);
		return (1);
	}
	mlx_loop(mlx);
	free_map(map);
	return (0);
}

/* int	main(int argc, char **argv)
{
	if (argc < 2)
		no_map();
	if (argc > 2)
		too_many_args();
	if (!name_check(argv[1]))
		wrong_format();
	
	return (0);
} */
