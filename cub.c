/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:33:23 by achater           #+#    #+#             */
/*   Updated: 2024/10/16 23:23:05 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void f()
{
	system("leaks cub3D");
}

// void	cleanup(my_mlx_t *mlx)
// {
// 	ft_dbl_free(mlx->map);
// 	mlx_delete_texture(mlx->texture->so_tex);
// 	mlx_delete_texture(mlx->texture->we_tex);
// 	mlx_delete_texture(mlx->texture->no_tex);
// 	mlx_delete_texture(mlx->texture->ea_tex);
// 	free(mlx->texture);
// }

int main(int ac, char **av)
{
	my_mlx_t	*mlx;

	atexit(f);
	if (ac != 2)
		error_mssg(INVALID_INPUT);
	else
	{
		check_extension(av[1]);
		mlx = malloc(sizeof(my_mlx_t));
		get_layout(mlx, av[1]);
		mlx->b_size = 80;
		mlx->width = 1280;
		mlx->height = 720;
		main_fct(mlx);
		return (0);
	}
}
