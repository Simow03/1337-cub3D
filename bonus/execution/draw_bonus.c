/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:08:58 by achater           #+#    #+#             */
/*   Updated: 2024/11/03 13:33:26 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_player_deriction(t_my_mlx *mlx, int x, int y)
{
	double	start_angle;
	double	angle;
	int		i;
	double	a;
	double	b;

	start_angle = mlx->angle - 30;
	angle = start_angle;
	while (angle < 60 + start_angle)
	{
		i = -1;
		a = x;
		b = y;
		while (++i < 25)
		{
			a += cos(angle * M_PI / 180);
			b += sin(angle * M_PI / 180);
			mlx_put_pixel(mlx->img, a, b, ft_pixel(255, 215, 0, 160));
		}
		angle++;
	}
}

void	draw_player(t_my_mlx *mlx, int x, int y, int color)
{
	int	dx;
	int	dy;
	int	radius;

	radius = 5;
	dx = -radius;
	draw_player_deriction(mlx, x, y);
	while (dx <= radius)
	{
		dy = -radius;
		while (dy <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				mlx_put_pixel(mlx->img, x + dx, y + dy, color);
			dy++;
		}
		dx++;
	}
}

void	draw_sprite(t_my_mlx *mlx, mlx_texture_t *s_t, int x, int y)
{
	int	pos_x;
	int	pos_y;
	int	index;

	s_t->height = s_t->height;
	pos_x = (mlx->width - s_t->width) / 2;
	pos_y = mlx->height - s_t->height;
	while (++x < (int)s_t->width)
	{
		y = -1;
		while (++y < (int)s_t->height)
		{
			index = (y * s_t->width + x) * s_t->bytes_per_pixel;
			if (s_t->pixels[index] != 0
				|| s_t->pixels[index + 1] != 0
				|| s_t->pixels[index + 2] != 0
				|| s_t->pixels[index + 3] != 0)
			{
				mlx_put_pixel(mlx->img, pos_x + x, pos_y + y,
					ft_pixel(s_t->pixels[index],
						s_t->pixels[index + 1], s_t->pixels[index + 2],
						s_t->pixels[index + 3]));
			}
		}
	}
}

void	draw_mlx(t_my_mlx *mlx)
{
	ray_casting(mlx);
	draw_mini_map(mlx);
}

void	main_fct(t_my_mlx *mlx)
{
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", 0);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	initiate_angle_pos(mlx);
	load_sprite_frames(mlx);
	draw_mlx(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(mlx->mlx, hook_fct, mlx);
	mlx_loop(mlx->mlx);
	mlx_terminate(mlx->mlx);
}
