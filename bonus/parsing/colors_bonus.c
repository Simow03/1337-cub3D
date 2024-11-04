/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:29:50 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/04 12:16:28 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	is_map_character(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E' || c == ' '
		|| c == '\n' || c == 'O' || c == 'C')
		return (1);
	return (0);
}

int	ft_nan(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	validate_rgb_value(char **rgb)
{
	int	i;

	i = -1;
	while (rgb[++i])
	{
		if (!ft_nan(rgb[i]))
		{
			ft_dbl_free(rgb);
			error_mssg_2(COLORS);
		}
		if (ft_atof(rgb[i]) < 0 || ft_atof(rgb[i]) > 255
			|| ft_atof(rgb[i]) != ft_atoi(rgb[i]))
		{
			ft_dbl_free(rgb);
			error_mssg_2(COLORS);
		}
	}
}

unsigned int	rgb_to_uint(char *component)
{
	int				i;
	char			**rgb;
	int				count;
	int32_t			color;

	i = -1;
	count = 0;
	while (component[++i])
		if (component[i] == ',')
			count++;
	if (count != 2)
		error_mssg_2(COLORS);
	rgb = ft_split(component, ',');
	if (ft_dbl_strlen(rgb) != 3)
	{
		ft_dbl_free(rgb);
		error_mssg_2(COLORS);
	}
	validate_rgb_value(rgb);
	color = ft_pixel(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	return (ft_dbl_free(rgb), color);
}
