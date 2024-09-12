/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:58:19 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/12 17:00:57 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_texture(t_texture *texture)
{
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->ea = NULL;
	texture->f = NULL;
	texture->c = NULL;
}

int	is_valid_texture(char *component)
{
	if (!ft_strcmp(component, "NO") || !ft_strcmp(component, "SO")
		|| !ft_strcmp(component, "WE") || !ft_strcmp(component, "EA")
		|| !ft_strcmp(component, "F") || !ft_strcmp(component, "C"))
			return (1);
	return (0);
}

void	fill_texture(t_texture *texture, char **components)
{
	if (!ft_strcmp(components[0], "NO"))
		texture->no = ft_strdup(components[1]);
	else if (!ft_strcmp(components[0], "SO"))
		texture->so = ft_strdup(components[1]);
	else if (!ft_strcmp(components[0], "WE"))
		texture->we = ft_strdup(components[1]);
	else if (!ft_strcmp(components[0], "EA"))
		texture->ea = ft_strdup(components[1]);
	else if (!ft_strcmp(components[0], "F"))
		texture->f = ft_strdup(components[1]);
	else if (!ft_strcmp(components[0], "C"))
		texture->c = ft_strdup(components[1]);
}

void	check_paths(char **path)
{
	if (!ft_strcmp(path[0], "NO") || !ft_strcmp(path[0], "SO")
		|| !ft_strcmp(path[0], "EA") || !ft_strcmp(path[0], "WE"))
	{
		if (access(path[1], F_OK) == 0)
			return ;
		else
		{
			if (errno == ENOENT)
				error_mssg(NOT_EXIST);
			else if (errno == EACCES)
				error_mssg(PERMISSION);
			else
				error_mssg(CHECK_FILE);
		}
	}
	else
	{
		//check color
		return ;
	}
}

void	check_textures(char **layout)
{
	t_texture	*texture;
	char		**components = NULL;

	texture = malloc(sizeof(t_texture));
	init_texture(texture);
	int	i;

	i = -1;
	while (layout[++i] && i < 6)
	{
		components = ft_split_set(layout[i], "\t ");
		if (ft_dbl_strlen(components) != 2)
			error_mssg(TEXTURE_ARG);
		if (!is_valid_texture(components[0]))
			error_mssg(TEXTURE_ARG);
		check_paths(components);
		fill_texture(texture, components);
	}
}
