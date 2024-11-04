/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_neighbours_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:52:14 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/04 10:05:28 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	is_player_or_zero(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
		return (1);
	return (0);
}

int	valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'O' || c == 'C')
		return (1);
	return (0);
}

int	player_neighbs(char **layout)
{
	int	i;
	int	j;

	i = -1;
	while (layout[++i])
	{
		j = 0;
		while (layout[i][j])
		{
			if (is_player_or_zero(layout[i][j]))
			{
				if (!valid_map_char(layout[i][j - 1])
					|| !valid_map_char(layout[i][j + 1])
					|| !valid_map_char(layout[i + 1][j])
					|| !valid_map_char(layout[i - 1][j]))
					return (0);
			}
			j++;
		}
	}
	return (1);
}
