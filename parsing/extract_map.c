/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:02:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/14 22:49:45 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_surrounded_by_walls(char **layout)
{
	int	x;
	int	y;
	int	len;

	x = -1;
	len = ft_dbl_strlen(layout);
	while (layout[0][++x])
		if (layout[0][x] != '1' && layout[0][x] != ' ' && layout[0][x] != '\t')
			return (0);
	x = -1;
	while (layout[len - 1][++x])
		if (layout[len - 1][x] != '1' && layout[len - 1][x] != ' ' && layout[len - 1][x] != '\t')
			return (0);
	y = -1;
	while (layout[++y])
	{
		x = 0;
		len = ft_strlen(layout[y]);
		while (layout[y] && layout[y][x] == ' ')
			x++;
		if ((layout[y][x] != '1' && layout[y][x] != ' ' && layout[y][x] != '\t')
			|| (layout[y][len - 1] != '1' && layout[y][len - 1] != ' ' && layout[y][len - 1] != '\t'))
				return (0);
	}
	return (1);
}
