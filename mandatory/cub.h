/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 00:35:04 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/06 20:34:02 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define BUFFER_SIZE 42
# define TEXTURE_WIDTH 160
# define TEXTURE_HEIGHT 160

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../../MLX42/include/MLX42/MLX42.h"

# include "../libft/libft.h"

typedef enum e_error
{
	EXTENSION,
	INVALID_INPUT,
	MAP_CHAR,
	EMPTY_FILE,
	MAP_NOT_FOUND,
	NEWLINE_MAP,
	TEXTURE_ARG,
	NOT_EXIST,
	PERMISSION,
	CHECK_FILE,
	COLORS,
	WALLS,
	PLAYER_NOT_FOUND,
	NEIGHBOURS,
	DOORS,
	FRAMES
}	t_error;

typedef struct s_texture
{
	char			*c_dup;
	char			*f_dup;
	char			*no_dup;
	char			*so_dup;
	char			*we_dup;
	char			*ea_dup;
	unsigned int	f_clr;
	unsigned int	c_clr;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
}	t_texture;

typedef struct s_my_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	double			angle;
	double			x;
	double			y;
	int				width;
	int				height;
	unsigned int	cols;
	unsigned int	rows;
	int				b_size;
	int				is_vertical;
	mlx_texture_t	*curr_texture;
	double			x_h;
	double			y_h;
	double			x_v;
	double			y_v;
	double			wall_inter_x;
	double			wall_inter_y;
	double			wall_inter;
	t_texture		*texture;
	double			wall_height;
	double			wall_start;
	double			wall_end;
}	t_my_mlx;

void			main_fct(t_my_mlx *mlx);
void			hook_fct(void *param);
void			draw_mlx(t_my_mlx *mlx);
void			ray_casting(t_my_mlx *mlx);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			normalize_angle(double *angle);
double			find_right_dist(t_my_mlx *mlx, double a);
void			error_mssg(int flag);
void			error_mssg_2(int flag);
void			get_layout(t_my_mlx *mlx, char *av);
char			**trim_line(t_my_mlx *mlx, char *line);
char			*get_next_line(int fd);
void			check_textures(t_my_mlx *mlx, char **layout);
int				is_surrounded_by_walls(char **layout);
int				player_exists(char **layout);
void			get_which_texture_side(t_my_mlx *mlx, double ray_x,
					double ray_y);
unsigned int	get_texture_color(mlx_texture_t *tex, unsigned int x,
					unsigned int y);
void			adjust_color(mlx_image_t *image, unsigned int x, unsigned int y,
					unsigned int c);
double			get_text_x(t_my_mlx *mlx, double wall_inter);
double			get_tex_y(t_my_mlx *mlx, double y, double wall_height);
unsigned int	rgb_to_uint(char *component);
void			free_textures(t_my_mlx *mlx);
void			fill_map(t_my_mlx *mlx, char **layout);
char			*ft_gnl_strjoin(char *stored, char *buffer);
char			*ft_gnl_strchr(char *s, int c);
size_t			ft_gnl_strlen(char *s);
int				player_neighbs(char **layout);
int				is_map_character(char c);
#endif
