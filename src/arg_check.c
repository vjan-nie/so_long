/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:43:04 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/05/24 12:39:20 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	arg_check(int argc, char **argv)
{
	if (argc < 2)
		no_map();
	if (argc > 2)
		too_many_args();
	if (!name_check(argv[1]))
		wrong_format();
	return ;
}

int	name_check(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if (len < 5) // al menos 1 char + ".ber"
		return (0);
	if (ft_strncmp(s + len - 4, ".ber", 4) != 0)
		return (0);
	return (0);
}
