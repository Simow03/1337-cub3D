/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:02:44 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/19 22:20:02 by mstaali          ###   ########.fr       */
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

int check_zero_adjacent(char **layout)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j])
		{
			if (layout[i][j] == '0')
			{
				if ((j > 0 && !ft_strchr("01NSWE", layout[i][j - 1])) ||
				(layout[i][j + 1] && !ft_strchr("01NSWE", layout[i][j + 1])) ||
					(j == ft_strlen(layout[i]) - 1) ||
					(i > 0 && (j >= ft_strlen(layout[i-1]) || !ft_strchr("01NSWE", layout[i - 1][j]))) ||
					(layout[i + 1] && (j >= ft_strlen(layout[i+1]) || !ft_strchr("01NSWE", layout[i + 1][j]))))
						return (0);
			}
			j++;
        }
		i++;
	}
	return (1);
}

int	player_exists(char **layout)
{
	int	i;
	int	j;

	i = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j])
		{
			if (layout[i][j] == 'N' || layout[i][j] == 'W'
				|| layout[i][j] == 'E' || layout[i][j] == 'S')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
