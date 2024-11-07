/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:34:46 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/07 05:03:17 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	validate_map_chars(t_my_mlx *mlx, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		if (is_empty_line(map[i]))
		{
			free(mlx);
			error_mssg(MAP_CHAR);
		}
		j = -1;
		while (map[i][++j])
		{
			if (!is_map_character(map[i][j]))
			{
				free(mlx);
				error_mssg(MAP_CHAR);
			}
		}
	}
}

void	is_map_valid(t_my_mlx *mlx, char **map)
{
	validate_map_chars(mlx, map);
	if (!is_surrounded_by_walls(map))
	{
		free(mlx);
		error_mssg_2(WALLS);
	}
	if (!player_exists(map))
	{
		free(mlx);
		error_mssg_2(PLAYER_NOT_FOUND);
	}
	if (!player_neighbs(map))
	{
		free(mlx);
		error_mssg_2(NEIGHBOURS);
	}
}

char	**read_from_file(t_my_mlx *mlx, char *av)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	**layout;
	char	*new_line;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		free(mlx);
		error_mssg(EMPTY_FILE);
	}
	line = get_next_line(fd);
	tmp = get_next_line(fd);
	while (tmp)
	{
		new_line = line;
		line = ft_strjoin(line, tmp);
		free(new_line);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	layout = trim_line(mlx, line);
	return (free(line), layout);
}

void	check_player(t_my_mlx *mlx, char **layout)
{
	if (!player_exists(layout + 6))
	{
		free_textures(mlx);
		error_mssg_2(PLAYER_NOT_FOUND);
	}
	if (!player_neighbs(layout + 6))
	{
		free_textures(mlx);
		error_mssg_2(NEIGHBOURS);
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
}

void	split_textures(t_my_mlx *mlx, char **layout)
{
	char	**comps;
	int		i;

	i = 0;
	while (layout[i] && i < 6)
	{
		comps = ft_split_once(layout[i], " \t");
		if (!ft_strcmp(comps[0], "C") || !ft_strcmp(comps[0], "F"))
			assign_number(mlx, comps);
		else
			assign_texture(mlx, comps);
		i++;
	}
	ft_dbl_free(comps);
	if (!mlx->texture->c_dup || !mlx->texture->f_dup
		|| !mlx->texture->so_dup || !mlx->texture->no_dup
		|| !mlx->texture->ea_dup || !mlx->texture->we_dup)
	{
		free(mlx->texture);
		free(mlx);
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

void	load_textures(t_my_mlx *mlx)
{
	mlx->texture->no_tex = mlx_load_png(mlx->texture->no_dup);
	mlx->texture->so_tex = mlx_load_png(mlx->texture->so_dup);
	mlx->texture->we_tex = mlx_load_png(mlx->texture->we_dup);
	mlx->texture->ea_tex = mlx_load_png(mlx->texture->ea_dup);
	if (mlx->texture->ea_tex == NULL || mlx->texture->so_tex == NULL
		|| mlx->texture->no_tex == NULL || mlx->texture->so_tex == NULL)
	{
		ft_dbl_free(mlx->map);
		free(mlx);
		error_mssg(NOT_EXIST);
	}
}

void	get_layout(t_my_mlx *mlx, char *av)
{
	char	**layout;

	layout = read_from_file(mlx, av);
	init_textures(mlx);
	split_textures(mlx, layout);
	is_valid_color(mlx, mlx->texture->c_dup);
	is_valid_color(mlx, mlx->texture->f_dup);
	fill_colors(mlx);
	if (!*(layout + 6))
	{
		free(mlx);
		error_mssg(MAP_NOT_FOUND);
	}
	is_map_valid(mlx, layout + 6);
	fill_map(mlx, layout + 6);
	load_textures(mlx);
}
