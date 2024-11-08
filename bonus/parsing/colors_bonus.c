/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:29:50 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/08 04:07:59 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	is_map_character(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E' || c == ' '
		|| c == '\n' || c == 'O' || c == 'C')
		return (1);
	return (0);
}

void	fill_colors(t_my_mlx *mlx)
{
	char	**c_rgb;
	char	**f_rgb;

	c_rgb = ft_split_set(mlx->texture->c_dup, ", \t");
	f_rgb = ft_split_set(mlx->texture->f_dup, ", \t");
	mlx->texture->c_clr = ft_pixel(ft_atoi(c_rgb[0]),
			ft_atoi(c_rgb[1]), ft_atoi(c_rgb[2]), 255);
	mlx->texture->f_clr = ft_pixel(ft_atoi(f_rgb[0]),
			ft_atoi(f_rgb[1]), ft_atoi(f_rgb[2]), 255);
	ft_dbl_free(c_rgb);
	ft_dbl_free(f_rgb);
}

void	is_valid_color(t_my_mlx *mlx, char *color)
{
	int		comma;
	int		i;
	char	**rgb;

	i = 0;
	comma = 0;
	while (color[i])
	{
		if (color[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
	{
		free_textures(mlx);
		error_mssg_2(COLORS);
	}
	rgb = ft_split_set(color, ", \t");
	if (ft_dbl_strlen(rgb) != 3)
	{
		free_textures(mlx);
		error_mssg_2(COLORS);
	}
	check_number(mlx, rgb);
	ft_dbl_free(rgb);
}

void	check_number(t_my_mlx *mlx, char **digits)
{
	int	i;

	i = 0;
	while (digits[i])
	{
		if (ft_strlen(digits[i]) > 3)
		{
			free_textures(mlx);
			error_mssg_2(COLORS);
		}
		if (ft_atoi(digits[i]) < 0 || ft_atoi(digits[i]) > 255
			|| ft_atoi(digits[i]) == -1)
		{
			free_textures(mlx);
			error_mssg_2(COLORS);
		}
		i++;
	}
}

void	assign_number(t_my_mlx *mlx, char **comps)
{
	int	i;

	i = 0;
	while (comps[1][i] && (comps[1][i] == ' ' || comps[1][i] == '\t'))
		i++;
	if (!ft_strcmp(comps[0], "C") && !mlx->texture->c_dup)
		mlx->texture->c_dup = ft_strdup(comps[1]);
	else if (!ft_strcmp(comps[0], "F") && !mlx->texture->f_dup)
		mlx->texture->f_dup = ft_strdup(comps[1]);
}
