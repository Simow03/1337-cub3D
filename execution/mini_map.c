/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:13:31 by achater           #+#    #+#             */
/*   Updated: 2024/10/09 15:40:21 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_contour(my_mlx_t *mlx)
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
            mlx_put_pixel(mlx->img, i, k, ft_pixel(44, 44, 44, 255));
            mlx_put_pixel(mlx->img, i, (10 * 20) - 1 - k, ft_pixel(44, 44, 44, 255));
        }
	}
	j = -1;
    while (++j < (10 * 20))
	{
		k = -1;
        while (++k < 4)
        {
            mlx_put_pixel(mlx->img, k, j, ft_pixel(44, 44, 44, 255));
            mlx_put_pixel(mlx->img, (10 * 20) - 1 - k, j, ft_pixel(44, 44, 44, 255));
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

	i1 = mlx->x - 5 * mlx->block_size;
	j1= mlx->y - 5 * mlx->block_size;
	while(j < 10 * 20)
	{
		i = 0;
		while(i < 10 * 20)
		{
			i2 = i1 + (double)i / 20 * mlx->block_size;
			j2 = j1 + (double)j / 20 * mlx->block_size;
			if (j2 >= 0 && j2 < (double)mlx->rows * mlx->block_size && i2 >= 0 && i2 < (double)mlx->cols * mlx->block_size)
			{
				if (mlx->map[(int)j2 / mlx->block_size][(int)i2 / mlx->block_size] == '1')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(112, 128, 144, 255));
				else if (mlx->map[(int)j2 / mlx->block_size][(int)i2 / mlx->block_size] == 'C')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(139, 69, 19, 255));
				else if (mlx->map[(int)j2 / mlx->block_size][(int)i2 / mlx->block_size] == 'O')
					mlx_put_pixel(mlx->img, i, j, ft_pixel(144, 238, 144, 255));
				else
					mlx_put_pixel(mlx->img, i, j, ft_pixel(224, 240, 240, 255));
			}
			else
				mlx_put_pixel(mlx->img, i, j, ft_pixel(44, 44, 44, 255));
			i++;
		}
		j++;
	}
	double x = (mlx->x - i1) / mlx->block_size * 20;
	double y = (mlx->y - j1) / mlx->block_size * 20;

	draw_player(mlx, x, y , 5, ft_pixel(255, 165, 0, 255));
    draw_contour(mlx);
}
