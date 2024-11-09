/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:58:19 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/09 01:28:38 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	split_textures(t_my_mlx *mlx, char **layout)
{
	char	**comps;
	int		i;

	i = 0;
	while (layout[i] && i < 7)
	{
		comps = ft_split_once(layout[i], " \t");
		if (!ft_strcmp(comps[0], "C") || !ft_strcmp(comps[0], "F"))
			assign_number(mlx, comps);
		else
			assign_texture(mlx, comps);
		ft_dbl_free(comps);
		i++;
	}
	if (!mlx->texture->c_dup || !mlx->texture->f_dup
		|| !mlx->texture->so_dup || !mlx->texture->no_dup
		|| !mlx->texture->ea_dup || !mlx->texture->we_dup
		|| !mlx->texture->door_dup)
	{
		free_textures(mlx);
		error_mssg(TEXTURE_ARG);
	}
}

void	init_textures(t_my_mlx *mlx)
{
	mlx->texture = (t_texture *)malloc(sizeof(t_texture));
	if (!mlx->texture)
	{
		free(mlx);
		error_mssg(TEXTURE_ARG);
	}
	mlx->texture->c_dup = NULL;
	mlx->texture->f_dup = NULL;
	mlx->texture->no_dup = NULL;
	mlx->texture->so_dup = NULL;
	mlx->texture->we_dup = NULL;
	mlx->texture->ea_dup = NULL;
	mlx->texture->door_dup = NULL;
}

void	load_textures(t_my_mlx *mlx)
{
	mlx->texture->no_tex = mlx_load_png(mlx->texture->no_dup);
	mlx->texture->so_tex = mlx_load_png(mlx->texture->so_dup);
	mlx->texture->we_tex = mlx_load_png(mlx->texture->we_dup);
	mlx->texture->ea_tex = mlx_load_png(mlx->texture->ea_dup);
	mlx->texture->door_tex = mlx_load_png(mlx->texture->door_dup);
	if (mlx->texture->ea_tex == NULL || mlx->texture->so_tex == NULL
		|| mlx->texture->no_tex == NULL || mlx->texture->so_tex == NULL
		|| mlx->texture->door_tex == NULL)
	{
		ft_dbl_free(mlx->map);
		error_mssg(NOT_EXIST);
	}
}

void	assign_texture(t_my_mlx *mlx, char **comps)
{
	if (!ft_strcmp(comps[0], "NO") && !mlx->texture->no_dup)
		mlx->texture->no_dup = ft_strdup(comps[1]);
	else if (!ft_strcmp(comps[0], "SO") && !mlx->texture->so_dup)
		mlx->texture->so_dup = ft_strdup(comps[1]);
	else if (!ft_strcmp(comps[0], "WE") && !mlx->texture->we_dup)
		mlx->texture->we_dup = ft_strdup(comps[1]);
	else if (!ft_strcmp(comps[0], "EA") && !mlx->texture->ea_dup)
		mlx->texture->ea_dup = ft_strdup(comps[1]);
	else if (!ft_strcmp(comps[0], "DO") && !mlx->texture->door_dup)
		mlx->texture->door_dup = ft_strdup(comps[1]);
}
