/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:05 by achater           #+#    #+#             */
/*   Updated: 2024/11/03 11:44:35 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	initiate_angle_pos(t_my_mlx *mlx)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < mlx->rows)
	{
		j = -1;
		while (++j < mlx->cols)
		{
			if (mlx->map[i][j] == 'N')
				mlx->angle = 270;
			else if (mlx->map[i][j] == 'E')
				mlx->angle = 0;
			else if (mlx->map[i][j] == 'S')
				mlx->angle = 90;
			else if (mlx->map[i][j] == 'W')
				mlx->angle = 180;
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'E'
				|| mlx->map[i][j] == 'S' || mlx->map[i][j] == 'W')
			{
				mlx->x = j * mlx->b_size + mlx->b_size / 2;
				mlx->y = i * mlx->b_size + mlx->b_size / 2;
			}
		}
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


void	draw_mlx(t_my_mlx *mlx)
{
	ray_casting(mlx);
}

void	main_fct(t_my_mlx *mlx)
{
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", 0);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	initiate_angle_pos(mlx);
	draw_mlx(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(mlx->mlx, hook_fct, mlx);
	mlx_loop(mlx->mlx);
	mlx_terminate(mlx->mlx);
}
