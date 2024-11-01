/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:24:22 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/30 17:41:42 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	extract_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign *= (-1);
		i++;
	}
	return (i);
}

double	extract_number(const char *str, double *decimal,
		int *decimal_places, int i)
{
	double	result;

	result = 0;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == '.' || str[i] == ','))
	{
		if (str[i] == '.' || str[i] == ',')
		{
			i++;
			while (str[i] && ft_isdigit(str[i]))
			{
				*decimal = *decimal * 10 + (str[i] - '0');
				(*decimal_places)++;
				i++;
			}
			break ;
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;
	double	decimal;
	int		decimal_places;

	sign = 1;
	decimal = 0;
	decimal_places = 0;
	i = extract_sign(str, &sign);
	result = extract_number(str, &decimal, &decimal_places, i);
	while (decimal_places > 0)
	{
		decimal /= 10;
		decimal_places--;
	}
	return ((result + decimal) * sign);
}
