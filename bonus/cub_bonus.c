/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:33:23 by achater           #+#    #+#             */
/*   Updated: 2024/11/02 00:39:38 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	free_textures(t_my_mlx *mlx)
{
	mlx_delete_texture(mlx->texture->no_tex);
	mlx_delete_texture(mlx->texture->so_tex);
	mlx_delete_texture(mlx->texture->ea_tex);
	mlx_delete_texture(mlx->texture->we_tex);
	mlx_delete_texture(mlx->texture->door_tex);
	free(mlx->texture);
	free(mlx);
}

void	check_extension(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '.')
		i++;
	if (av[i] != '.')
		error_mssg(EXTENSION);
	if (!ft_strcmp(&av[i], ".cub"))
		return ;
	error_mssg(EXTENSION);
}

int	main(int ac, char **av)
{
	t_my_mlx	*mlx;

	if (ac != 2)
		error_mssg(INVALID_INPUT);
	else
	{
		check_extension(av[1]);
		mlx = malloc(sizeof(t_my_mlx));
		get_layout(mlx, av[1]);
		mlx->b_size = 80;
		mlx->width = 1280;
		mlx->height = 720;
		main_fct(mlx);
		return (0);
	}
}
