/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:58:19 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/17 00:11:48 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_before_tex(my_mlx_t *mlx, char **components)
{
	ft_dbl_free(components);
	free(mlx);
}

void	free_after_tex(my_mlx_t *mlx, t_texture *texture, char **components)
{
	if (texture->no_tex)
		mlx_delete_texture(texture->no_tex);
	if (texture->so_tex)
		mlx_delete_texture(texture->so_tex);
	if (texture->we_tex)
		mlx_delete_texture(texture->we_tex);
	if (texture->ea_tex)
		mlx_delete_texture(texture->ea_tex);
	if (texture->door_tex)
		mlx_delete_texture(texture->door_tex);
	free(texture);
	ft_dbl_free(components);
	free(mlx);
}

int	is_valid_texture(char *component)
{
	if (!ft_strcmp(component, "NO") || !ft_strcmp(component, "SO")
		|| !ft_strcmp(component, "WE") || !ft_strcmp(component, "EA")
		|| !ft_strcmp(component, "F") || !ft_strcmp(component, "C")
		|| !ft_strcmp(component, "DO"))
			return (1);
	return (0);
}

unsigned int	rgb_to_uint(char *component)
{
	int				i;
	char			**rgb;
	int				count;
	int32_t			color;

	i = -1;
	count = 0;
	while (component[++i])
		if (component[i] == ',')
			count++;
	if (count != 2)
		error_mssg(COLORS);
	rgb = ft_split(component, ',');
	if (ft_dbl_strlen(rgb) != 3)
	{
		// free_after_tex(mlx, texture, components);
		ft_dbl_free(rgb);
		error_mssg(COLORS);
	}
	i = -1;
	while (rgb[++i])
		if (ft_atof(rgb[i]) < 0 || ft_atof(rgb[i]) > 255 || ft_atof(rgb[i]) != ft_atoi(rgb[i]))
		{
			// free_after_tex(mlx, texture, components);
			ft_dbl_free(rgb);
			error_mssg(COLORS);
		}
	color = ft_pixel(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	return (ft_dbl_free(rgb), color);
}

void	fill_texture(my_mlx_t *mlx, char **layout)
{
	int			i;
	t_texture	*texture;
	char		**components;

	i = -1;
	texture = malloc(sizeof(t_texture));
	while (layout[++i] && i < 7)
	{
		components = ft_split_set(layout[i], "\t ");
		if (!ft_strcmp(components[0], "NO"))
			texture->no_tex = mlx_load_png(components[1]);
		else if (!ft_strcmp(components[0], "SO"))
			texture->so_tex = mlx_load_png(components[1]);
		else if (!ft_strcmp(components[0], "WE"))
			texture->we_tex = mlx_load_png(components[1]);
		else if (!ft_strcmp(components[0], "EA"))
			texture->ea_tex = mlx_load_png(components[1]);
		else if (!ft_strcmp(components[0], "DO"))
			texture->door_tex = mlx_load_png(components[1]);
		else if (!ft_strcmp(components[0], "F"))
			texture->f_clr = rgb_to_uint(components[1]);
		else if (!ft_strcmp(components[0], "C"))
			texture->c_clr = rgb_to_uint(components[1]);
		if (!texture->no_tex || !texture->so_tex || !texture->we_tex
			|| !texture->ea_tex || !texture->door_tex)
		{
			error_mssg(NOT_EXIST);
		}
		ft_dbl_free(components);
		components = NULL;
	}
	mlx->texture = texture;
}

void	init_texture(t_texture *texture)
{
	texture->no_tex = NULL;
	texture->so_tex = NULL;
	texture->we_tex = NULL;
	texture->ea_tex = NULL;
	texture->door_tex = NULL;
}

void	check_textures(my_mlx_t *mlx, char **layout)
{
	char		**components;

	components = NULL;
	int	i;

	i = -1;
	while (layout[++i] && i < 7)
	{
		components = ft_split_set(layout[i], "\t ");
		if (!components || ft_dbl_strlen(components) != 2)
		{
			free_before_tex(mlx, components);
			error_mssg(TEXTURE_ARG);
		}
		if (!is_valid_texture(components[0]))
		{
			free_before_tex(mlx, components);
			error_mssg(TEXTURE_ARG);
		}
		ft_dbl_free(components);
		components = NULL;
	}
	fill_texture(mlx, layout);
}
