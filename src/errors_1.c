/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:03:52 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 11:52:53 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	no_map(void)
{
	ft_printf("Can't start without a map!\n");
	exit(1);
}

void	too_many_args(void)
{
	ft_printf("Too many args. Choose one map\n");
	exit(1);
}

void	wrong_format(void)
{
	ft_printf("Invalid format: .ber map needed\n");
	exit(1);
}

void	map_load_error(void)
{
	ft_putstr_fd("Map load error\n", 2);
	exit(1);
}

void	invalid_map(void)
{
	ft_putstr_fd("Invalid map\n", 2);
	exit(1);
}
