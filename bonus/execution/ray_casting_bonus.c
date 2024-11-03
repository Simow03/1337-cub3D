/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:48:43 by achater           #+#    #+#             */
/*   Updated: 2024/11/03 13:38:28 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	normalize_angle(double *angle)
{
	*angle = fmod(*angle, 360);
	if (*angle < 0)
		*angle += 360.0;
}

void	painting(t_my_mlx *mlx, double screen_x)
{
	double			y;
	int				tex_x;
	int				tex_y;
	unsigned int	pixel_color;
	int				x;

	y = mlx->wall_start - 1;
	x = -1;
	if (mlx->door == 1)
		mlx->curr_texture = mlx->texture->door_tex;
	else
		get_which_texture_side(mlx, mlx->wall_inter_x, mlx->wall_inter_y);
	tex_x = get_text_x(mlx, mlx->wall_inter);
	while (++x < mlx->wall_start)
		mlx_put_pixel(mlx->img, screen_x, x, mlx->texture->c_clr);
	while (++y < mlx->wall_end)
	{
		tex_y = get_tex_y(mlx, y, mlx->wall_height);
		pixel_color = get_texture_color(mlx->curr_texture, tex_x, tex_y);
		if (y >= 0 && y < mlx->height)
			adjust_color(mlx->img, screen_x, y, pixel_color);
	}
	y--;
	while (++y < mlx->height)
		mlx_put_pixel(mlx->img, screen_x, y, mlx->texture->f_clr);
}

void	ray_casting(t_my_mlx *mlx)
{
	double	step;
	double	screen_x;
	double	c_distance;
	int		ray_count;
	double	a ;

	normalize_angle(&a);
	ray_count = -1;
	step = 60.0 / mlx->width;
	a = mlx->angle - 30;
	screen_x = 0;
	while (++ray_count < mlx->width)
	{
		normalize_angle(&a);
		c_distance = find_right_dist(mlx, a);
		mlx->wall_height = (mlx->height / c_distance) * (mlx->b_size + 40);
		mlx->wall_start = (mlx->height / 2) - (mlx->wall_height / 2);
		mlx->wall_end = mlx->wall_start + mlx->wall_height;
		(mlx->wall_start < 0.0) && (mlx->wall_start = 0.0);
		(mlx->wall_end > mlx->height) && (mlx->wall_end = mlx->height);
		painting(mlx, screen_x);
		1 && (a += step, screen_x++);
	}
}
