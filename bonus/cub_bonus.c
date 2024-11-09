/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:33:23 by achater           #+#    #+#             */
/*   Updated: 2024/11/09 01:26:45 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_exit(t_my_mlx *mlx)
{
	int	i;

	i = -1;
	mlx_delete_texture(mlx->texture->no_tex);
	mlx_delete_texture(mlx->texture->so_tex);
	mlx_delete_texture(mlx->texture->ea_tex);
	mlx_delete_texture(mlx->texture->we_tex);
	mlx_delete_texture(mlx->texture->door_tex);
	ft_dbl_free(mlx->map);
	while (++i < mlx->num_frames)
		if (mlx->sprite_textures[i])
			mlx_delete_texture(mlx->sprite_textures[i]);
	free(mlx->sprite_textures);
	free(mlx->sprite_frames);
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
	free(mlx->texture->door_dup);
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

void	f(void)
{
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_my_mlx	*mlx;

	atexit(f);
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
