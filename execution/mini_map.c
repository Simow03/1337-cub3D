/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:13:31 by achater           #+#    #+#             */
/*   Updated: 2024/10/16 16:29:24 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_contour(my_mlx_t *mlx, int32_t color)
{
	int	i;
	int	j;
	int	k;

	i = -1;
    while (++i < (10 * 20))
	{
		k = -1;
        while (++k < 4)
        {
            mlx_put_pixel(mlx->img, i, k, color);
            mlx_put_pixel(mlx->img, i, (10 * 20) - 1 - k, color);
        }
	}
	j = -1;
    while (++j < (10 * 20))
	{
		k = -1;
        while (++k < 4)
        {
            mlx_put_pixel(mlx->img, k, j, color);
            mlx_put_pixel(mlx->img, (10 * 20) - 1 - k, j, color);
        }
	}
}

void	draw_mini_map(my_mlx_t *mlx)
{
	int i = 0;
	int j = 0;
	double i1;
	double j1;
	double j2;
	double i2;

	i1 = mlx->x - 5 * mlx->b_size;
	j1= mlx->y - 5 * mlx->b_size;
	while(j < 10 * 20)
	{
		i = 0;
		while(i < 10 * 20)
		{
			i2 = i1 + (double)i / 20 * mlx->b_size;
			j2 = j1 + (double)j / 20 * mlx->b_size;
			if (j2 >= 0 && j2 < (double)mlx->rows * mlx->b_size && i2 >= 0 && i2 < (double)mlx->cols * mlx->b_size)
			{
				if (mlx->map[(int)j2 / mlx->b_size][(int)i2 / mlx->b_size] == '1')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(199, 21, 133, 255)); //walls
				else if (mlx->map[(int)j2 / mlx->b_size][(int)i2 / mlx->b_size] == 'C')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(128, 0, 128, 255)); //closed doors
				else if (mlx->map[(int)j2 / mlx->b_size][(int)i2 / mlx->b_size] == 'O')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(186, 85, 211, 255)); //open doors
				else
					mlx_put_pixel(mlx->img, i, j, ft_pixel(221, 160, 221, 255)); //empty spaces
			}
			else
				mlx_put_pixel(mlx->img, i, j, ft_pixel(75, 0, 130, 255)); //outside 
			i++;
		}
		j++;
	}
	double x = (mlx->x - i1) / mlx->b_size * 20;
	double y = (mlx->y - j1) / mlx->b_size * 20;

	draw_player(mlx, x, y , 5, ft_pixel(50, 255, 50, 255)); //player color 
	draw_contour(mlx, ft_pixel(255, 20, 147, 255)); // map contour color
}
