/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:11:26 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/03 00:42:20 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	fill_frame_paths(mlx_texture_t **sprite_textures)
{
	sprite_textures[0] = mlx_load_png("assets/init_state.png");
	if (!sprite_textures[0])
		error_mssg(FRAMES);
	sprite_textures[1] = mlx_load_png("assets/animate_1.png");
	if (!sprite_textures[1])
		error_mssg(FRAMES);
	sprite_textures[2] = mlx_load_png("assets/animate_2.png");
	if (!sprite_textures[2])
		error_mssg(FRAMES);
	sprite_textures[3] = mlx_load_png("assets/animate_3.png");
	if (!sprite_textures[3])
		error_mssg(FRAMES);
	sprite_textures[4] = mlx_load_png("assets/animate_4.png");
	if (!sprite_textures[4])
		error_mssg(FRAMES);
	sprite_textures[5] = mlx_load_png("assets/animate_5.png");
	if (!sprite_textures[5])
		error_mssg(FRAMES);
	sprite_textures[6] = mlx_load_png("assets/animate_6.png");
	if (!sprite_textures[6])
		error_mssg(FRAMES);
}

void	load_sprite_frames(my_mlx_t *mlx)
{
	int	i;

	mlx->num_frames = 7;
	mlx->curr_frame = 0;
    mlx->is_animated = 0;
    mlx->last_frame_time = mlx_get_time();
	mlx->sprite_textures = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * mlx->num_frames);
	if (!mlx->sprite_textures)
		error_mssg(FRAMES);
	fill_frame_paths(mlx->sprite_textures);
	mlx->sprite_frames = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * mlx->num_frames);
	//need to delete & free textures
	if (!mlx->sprite_frames)
		error_mssg(FRAMES);
	i = -1;
	while (++i < mlx->num_frames)
	{
		mlx->sprite_frames[i] = mlx_texture_to_image(mlx->mlx, mlx->sprite_textures[i]);
		if (!mlx->sprite_frames[i])
			error_mssg(FRAMES);
	}
}
