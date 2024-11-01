/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 04:17:18 by mstaali           #+#    #+#             */
/*   Updated: 2024/11/01 04:25:27 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split_once(char const *s, const char *set)
{
	char	**array;
	size_t	i;

	if (!s)
		return (NULL);
	array = (char **)malloc(3 * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (s[i] && !is_set_char(set, s[i]))
		i++;
	array[0] = ft_substr(s, 0, i);
	if (!array[0])
		return (ft_free_array(array));
	while (s[i] && !is_set_char(set, s[i]))
		i++;
	array[1] = ft_substr(s, i, ft_strlen(s) - i);
	if (!array[1])
		return (ft_free_array(array));
	array[2] = NULL;
	return (array);
}
