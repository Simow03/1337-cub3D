/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:19:47 by mstaali           #+#    #+#             */
/*   Updated: 2023/11/03 10:38:51 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	s_len;

	s_len = 0;
	while (size && src[s_len] && s_len < size - 1)
	{
		dest[s_len] = src[s_len];
		s_len++;
	}
	if (size > 0)
		dest[s_len] = '\0';
	while (src[s_len])
		s_len++;
	return (s_len);
}
