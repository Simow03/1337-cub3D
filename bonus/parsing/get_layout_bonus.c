/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_layout_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:34:46 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/08 04:10:11 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	validate_map_chars(t_my_mlx *mlx, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_map_character(map[i][j]))
			{
				free_textures(mlx);
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
		free_textures(mlx);
		error_mssg_2(WALLS);
	}
	if (!player_exists(map))
	{
		free_textures(mlx);
		error_mssg_2(PLAYER_NOT_FOUND);
	}
	if (!player_neighbs(map))
	{
		free_textures(mlx);
		error_mssg_2(NEIGHBOURS);
	}
	if (!is_valid_doors(map))
	{
		free_textures(mlx);
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

void	get_layout(t_my_mlx *mlx, char *av)
{
	char	**layout;

	layout = read_from_file(mlx, av);
	init_textures(mlx);
	split_textures(mlx, layout);
	is_valid_color(mlx, mlx->texture->c_dup);
	is_valid_color(mlx, mlx->texture->f_dup);
	fill_colors(mlx);
	if (!*(layout + 7))
	{
		free_textures(mlx);
		error_mssg(MAP_NOT_FOUND);
	}
	is_map_valid(mlx, layout + 7);
	fill_map(mlx, layout + 7);
	ft_dbl_free(layout);
	load_textures(mlx);
}
