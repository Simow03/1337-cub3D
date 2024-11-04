/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_layout_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:34:46 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/04 10:04:55 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	validate_map_chars(t_my_mlx *mlx, char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
		{
			free(mlx);
			free(line);
			error_mssg(NEWLINE_MAP);
		}
		if (!is_map_character(line[i]))
		{
			free(mlx);
			free(line);
			error_mssg(MAP_CHAR);
		}
		i++;
	}
}

void	is_map_valid(t_my_mlx *mlx, char *line)
{
	int	i;
	int	texture;

	if (!line)
	{
		free(mlx);
		error_mssg(EMPTY_FILE);
	}
	i = 0;
	texture = 0;
	while (line[i] && texture < 7)
	{
		if (line[i] == '\n' && line[i + 1] != '\n')
			texture++;
		i++;
	}
	validate_map_chars(mlx, line, i);
}

char	*read_from_file(t_my_mlx *mlx, char *av)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	*line2;
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
	line2 = trim_line(mlx, line);
	return (free(line), line2);
}

void	check_player(t_my_mlx *mlx, char **layout)
{
	if (!player_exists(layout + 7))
	{
		free_textures(mlx);
		error_mssg_2(PLAYER_NOT_FOUND);
	}
	if (!player_neighbs(layout + 7))
	{
		free_textures(mlx);
		error_mssg_2(NEIGHBOURS);
	}
}

void	get_layout(t_my_mlx *mlx, char *av)
{
	char	*line;
	char	**layout;

	line = read_from_file(mlx, av);
	is_map_valid(mlx, line);
	layout = ft_split(line, '\n');
	free(line);
	check_textures(mlx, layout);
	if (!is_surrounded_by_walls(layout + 7))
	{
		free_textures(mlx);
		error_mssg_2(WALLS);
	}
	check_player(mlx, layout);
	if (!is_valid_doors(layout + 7))
	{
		free_textures(mlx);
		error_mssg_2(DOORS);
	}
	fill_map(mlx, layout + 7);
	ft_dbl_free(layout);
}
