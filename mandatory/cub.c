/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:33:23 by achater           #+#    #+#             */
/*   Updated: 2024/11/07 23:45:26 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_exit(t_my_mlx *mlx)
{
	mlx_delete_texture(mlx->texture->no_tex);
	mlx_delete_texture(mlx->texture->so_tex);
	mlx_delete_texture(mlx->texture->ea_tex);
	mlx_delete_texture(mlx->texture->we_tex);
	ft_dbl_free(mlx->map);
	free_textures(mlx);
}

void	free_textures(t_my_mlx *mlx)
{
	free(mlx->texture->c_dup);
	free(mlx->texture->f_dup);
	free(mlx->texture->no_dup);
	free(mlx->texture->so_dup);
	free(mlx->texture->ea_dup);
	free(mlx->texture->we_dup);
	free(mlx->texture);
	free(mlx);
}

void	check_extension(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '.')
		i++;
	if (i == 0)
		error_mssg(EXTENSION);
	if (av[i] != '.')
		error_mssg(EXTENSION);
	if (!ft_strcmp(&av[i], ".cub"))
		return ;
	error_mssg(EXTENSION);
}

void	f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	atexit(f);
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
		ft_exit(mlx);
		return (0);
	}
}
