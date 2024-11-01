/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:02:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/01 05:22:21 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_vert(char **layout, int len, int x, int y)
{
	while (layout[++y])
	{
		x = 0;
		len = ft_strlen(layout[y]);
		while (layout[y] && layout[y][x] == ' ')
			x++;
		if ((layout[y][x] != '1' && layout[y][x] != ' '
			&& layout[y][x] != '\t')
			|| (layout[y][len - 1] != '1' && layout[y][len - 1] != ' '
				&& layout[y][len - 1] != '\t'))
			return (0);
	}
	return (1);
}

int	is_surrounded_by_walls(char **layout)
{
	int	x;
	int	y;
	int	len;

	x = -1;
	len = ft_dbl_strlen(layout);
	if (len == 0)
		error_mssg(NEWLINE_MAP);
	while (layout[0][++x])
		if (layout[0][x] != '1' && layout[0][x] != ' ' && layout[0][x] != '\t')
			return (0);
	x = -1;
	while (layout[len - 1][++x])
		if (layout[len - 1][x] != '1' && layout[len - 1][x] != ' '
			&& layout[len - 1][x] != '\t')
			return (0);
	y = -1;
	if (!check_vert(layout, len, x, y))
		return (0);
	return (1);
}

int	player_exists(char **layout)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j])
		{
			if (layout[i][j] == 'N' || layout[i][j] == 'W'
				|| layout[i][j] == 'E' || layout[i][j] == 'S')
			{
				count++;
				if (count > 1)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (count);
}
