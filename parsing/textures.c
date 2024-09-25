/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:12:34 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/25 00:50:19 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*get_which_texture_side(my_mlx_t *mlx)
{
	if (mlx->is_vertical)
	{
		if (cos(mlx->angle) > 0)
			mlx->curr_texture = mlx->texture->ea;
		else
			mlx->curr_texture = mlx->texture->we;
	}
	else
	{
		if (sin(mlx->angle) > 0)
			mlx->curr_texture = mlx->texture->so;
		else
			mlx->curr_texture = mlx->texture->no;
	}
}
