/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:31:42 by achater           #+#    #+#             */
/*   Updated: 2024/11/02 00:18:35 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	open_close_door(my_mlx_t *mlx)
{
	double	x;
	double	y;
	int		i;
	int		j;

	x = mlx->x + 80.0 * cos((mlx->angle) * M_PI / 180);
	y = mlx->y + 80.0 * sin ((mlx->angle) * M_PI / 180);
	i = (int)(y / mlx->b_size);
	j = (int)(x / mlx->b_size);
	if (mlx->map[i][j] == 'C')
		mlx->map[i][j] = 'O';
	else if (mlx->map[i][j] == 'O' &&
		(!(mlx->map[(int)(mlx->y / mlx->b_size)]
			[(int)(mlx->x / mlx->b_size)] == 'O'
		&& (int)(mlx->y / mlx->b_size) == i
		&& (int)(mlx->x / mlx->b_size) == j)))
		mlx->map[i][j] = 'C';
}
