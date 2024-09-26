/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:12:34 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/26 01:29:53 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_which_texture_side(my_mlx_t *mlx)
{
	if (mlx->is_vertical)
	{
		if (cos(mlx->angle) > 0)
			mlx->curr_texture = mlx->texture->ea_tex;
		else
			mlx->curr_texture = mlx->texture->we_tex;
	}
	else
	{
		if (sin(mlx->angle) > 0)
			mlx->curr_texture = mlx->texture->so_tex;
		else
			mlx->curr_texture = mlx->texture->no_tex;
	}
}

double	get_text_x(my_mlx_t *mlx, double wall_inter)
{
	double	tex_x;
	double	offset;

	offset = fmod(wall_inter, mlx->block_size);
	tex_x = (offset * mlx->curr_texture->width) / mlx->block_size;
	return (tex_x);
}

double	get_tex_y(my_mlx_t *mlx, double y, double wall_height)
{
	double	tex_y;
	double	wall_y;

	wall_y = y - (( mlx->height / 2) - (wall_height / 2));
	tex_y = (wall_y * mlx->curr_texture->height) / wall_height;
	return (tex_y);
}

uint32_t get_texture_color(mlx_texture_t *texture, int x, int y)
{
    if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
        return 0;

    int index = (y * texture->width + x) * texture->bytes_per_pixel;
    return *(uint32_t*)&texture->pixels[index];
}
