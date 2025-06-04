/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:43:04 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/06/04 14:11:19 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	arg_check(int argc, char **argv)
{
	if (argc < 2)
		arg_error("Can't start without a map!\n");
	if (argc > 2)
		arg_error("Too many args. Choose one map\n");
	if (!name_check(argv[1]))
		arg_error("Invalid format: .ber map needed\n");
	return ;
}

int	name_check(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 5)
		return (0);
	if (ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (0);
	return (1);
}
