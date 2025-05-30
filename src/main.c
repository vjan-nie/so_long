/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:53 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:12 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	char	**map;

	arg_check(argc, argv);
	map = load_map(argv[1]);
	if (map == NULL)
		map_error(NULL, "Map load error\n");
	if (!map_is_valid(map))
		map_error(map, "Invalid map\n");
	mlx = mlx_init();
	if (!mlx)
		ft_mlx_error(mlx);
	so_long(mlx, map);
	return (0);
}
