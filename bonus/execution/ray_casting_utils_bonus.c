/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:37:08 by achater           #+#    #+#             */
/*   Updated: 2024/11/03 13:38:37 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	ray_h_helper(t_my_mlx *mlx, double *ax, double *ay, double a)
{
	double			xstep;
	double			ystep;
	unsigned int	m_x;
	unsigned int	m_y;

	ystep = mlx->b_size;
	xstep = ystep / tan(a * M_PI / 180);
	(sin(a * M_PI / 180) <= 0 && ystep > 0) && (ystep *= -1);
	(cos(a * M_PI / 180) <= 0 && xstep > 0) && (xstep *= -1);
	(cos(a * M_PI / 180) > 0 && xstep < 0) && (xstep *= -1);
	while (*ax >= 0 && *ay >= 0 && *ax < (mlx->cols * mlx->b_size)
		&& *ay < (mlx->rows * mlx->b_size))
	{
		1 && (m_x = (int)(*ax / mlx->b_size), m_y = (int)(*ay / mlx->b_size));
		if (m_x >= 0 && m_x < mlx->cols && m_y >= 0 && m_y < mlx->rows)
		{
			if (mlx->map[m_y][m_x] == '1' || mlx->map[m_y][m_x] == 'C')
			{
				(mlx->map[m_y][m_x] == 'C') && (mlx->h_door = 1);
				(mlx->map[m_y][m_x] != 'C') && (mlx->h_door = 0);
				break ;
			}
		}
		1 && (*ax += xstep, *ay += ystep);
	}
}

void	ray_v_helper(t_my_mlx *mlx, double *ax, double *ay, double a)
{
	double			xstep;
	double			ystep;
	unsigned int	m_x;
	unsigned int	m_y;

	xstep = mlx->b_size;
	ystep = xstep * tan(a * M_PI / 180);
	(cos(a * M_PI / 180) <= 0) && (xstep *= -1);
	(sin(a * M_PI / 180) <= 0 && ystep > 0) && (ystep *= -1);
	(sin(a * M_PI / 180) > 0 && ystep < 0) && (ystep *= -1);
	while (*ax >= 0 && *ay >= 0 && *ax < (mlx->cols * mlx->b_size)
		&& *ay < (mlx->rows * mlx->b_size))
	{
		1 && (m_x = (int)(*ax / mlx->b_size), m_y = (int)(*ay / mlx->b_size));
		if (m_x >= 0 && m_x < mlx->cols && m_y >= 0 && m_y < mlx->rows)
		{
			if (mlx->map[m_y][m_x] == '1' || mlx->map[m_y][m_x] == 'C')
			{
				(mlx->map[m_y][m_x] == 'C') && (mlx->v_door = 1);
				(mlx->map[m_y][m_x] != 'C') && (mlx->v_door = 0);
				break ;
			}
		}
		1 && (*ax += xstep, *ay += ystep);
	}
}

double	horizontal_distance(t_my_mlx *mlx, double Px, double Py, double a)
{
	double	ax;
	double	ay;
	double	h_distance;

	normalize_angle(&a);
	if (sin(a * M_PI / 180) > 0)
		ay = floor(Py / mlx->b_size) * mlx->b_size + mlx->b_size;
	else
		ay = floor(Py / mlx->b_size) * mlx->b_size - 0.0001;
	ax = Px - (Py - ay) / tan(a * M_PI / 180);
	ray_h_helper(mlx, &ax, &ay, a);
	h_distance = sqrt(pow(ax - mlx->x, 2) + pow(ay - mlx->y, 2));
	mlx->x_h = ax;
	mlx->y_h = ay;
	return (h_distance);
}

double	vertical_distance(t_my_mlx *mlx, double Px, double Py, double a)
{
	double	ax;
	double	ay;
	double	v_distance;

	normalize_angle(&a);
	if (cos(a * M_PI / 180) > 0)
		ax = floor(Px / mlx->b_size) * mlx->b_size + mlx->b_size;
	else
		ax = floor(Px / mlx->b_size) * mlx->b_size - 0.0001;
	ay = Py + (ax - Px) * tan(a * M_PI / 180);
	ray_v_helper(mlx, &ax, &ay, a);
	v_distance = sqrt(pow(ax - mlx->x, 2) + pow(ay - mlx->y, 2));
	mlx->x_v = ax;
	mlx->y_v = ay;
	return (v_distance);
}

double	find_right_dist(t_my_mlx *mlx, double a)
{
	double	h_distance;
	double	v_distance;
	double	distance;

	h_distance = horizontal_distance(mlx, mlx->x, mlx->y, a);
	v_distance = vertical_distance(mlx, mlx->x, mlx->y, a);
	if (h_distance < v_distance)
	{
		distance = h_distance;
		mlx->wall_inter = mlx->x_h;
		mlx->wall_inter_x = mlx->x_h;
		mlx->wall_inter_y = mlx->y_h;
		mlx->is_vertical = 0;
		mlx->door = mlx->h_door;
	}
	else
	{
		distance = v_distance;
		mlx->wall_inter = mlx->y_v;
		mlx->wall_inter_x = mlx->x_v;
		mlx->wall_inter_y = mlx->y_v;
		mlx->is_vertical = 1;
		mlx->door = mlx->v_door;
	}
	return (distance * cos((a - mlx->angle) * M_PI / 180));
}
