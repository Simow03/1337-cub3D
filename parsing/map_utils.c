/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:13:51 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/02 17:36:00 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

char	*trim_line(t_my_mlx *mlx, char *line)
{
	char	*line2;

	line2 = ft_strtrim(line, "\n");
	if (!*line2)
	{
		free(line2);
		free(mlx);
		error_mssg(EMPTY_FILE);
	}
	return (line2);
}
