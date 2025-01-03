/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:13:51 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/09 18:17:06 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

static void	map_padding(t_my_mlx *mlx, char **layout)
{
	int	i;
	int	j;
	int	len;

	mlx->map = malloc((mlx->rows + 1) * sizeof(char *));
	if (!mlx->map)
		return ;
	i = -1;
	while (++i < (int)mlx->rows)
	{
		mlx->map[i] = malloc(mlx->cols + 1);
		len = ft_strlen(layout[i]);
		ft_strlcpy(mlx->map[i], layout[i], len + 1);
		j = len;
		while (j < (int)mlx->cols)
			mlx->map[i][j++] = '5';
		mlx->map[i][mlx->cols] = '\0';
	}
	mlx->map[mlx->rows] = NULL;
}

void	fill_map(t_my_mlx *mlx, char **layout)
{
	int		i;

	mlx->rows = ft_dbl_strlen(layout);
	mlx->cols = 0;
	i = 0;
	while (i < (int)mlx->rows)
	{
		if (ft_strlen(layout[i]) > mlx->cols)
			mlx->cols = ft_strlen(layout[i]);
		i++;
	}
	map_padding(mlx, layout);
}

void	check_map_newlines(t_my_mlx *mlx, char *line2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line2[i] && count < 7)
	{
		if (line2[i] == '\n' && line2[i + 1] != '\n')
			count++;
		i++;
	}
	while (line2[i])
	{
		if (line2[i] == '\n' && line2[i + 1] == '\n')
		{
			free(line2);
			free(mlx);
			error_mssg(NEWLINE_MAP);
		}
		i++;
	}
}

void	remove_whitespaces(t_my_mlx *mlx, char **layout)
{
	char	*trimmed;
	int		i;

	i = -1;
	while (layout[++i] && i < 7)
	{
		trimmed = ft_strtrim(layout[i], " \t\n");
		if (!trimmed)
		{
			ft_dbl_free(layout);
			free(mlx);
			error_mssg(TEXTURE_ARG);
		}
		free(layout[i]);
		layout[i] = trimmed;
	}
}

char	**trim_line(t_my_mlx *mlx, char *line)
{
	char	*line2;
	char	**layout;

	if (!line)
	{
		free(mlx);
		error_mssg(EMPTY_FILE);
	}
	line2 = ft_strtrim(line, "\n");
	if (!line2 || !*line2)
	{
		free(line2);
		free(mlx);
		error_mssg(EMPTY_FILE);
	}
	check_map_newlines(mlx, line2);
	free(line2);
	layout = ft_split(line, '\n');
	remove_whitespaces(mlx, layout);
	return (layout);
}
