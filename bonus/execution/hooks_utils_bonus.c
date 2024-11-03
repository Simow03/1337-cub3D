/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:35:46 by achater           #+#    #+#             */
/*   Updated: 2024/11/03 13:36:11 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	rotate(t_my_mlx *mlx, int angle)
{
	mlx->angle += angle;
	if (mlx->angle >= 360)
		mlx->angle -= 360;
	if (mlx->angle < 0)
		mlx->angle += 360;
}
