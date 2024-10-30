/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:56:23 by mstaali           #+#    #+#             */
/*   Updated: 2024/10/30 17:17:24 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(const char *s1, const char *set)
{
    char *buffer;
    size_t start;
    size_t end;
    size_t i;

    if (s1 == NULL)
        return (NULL);
    if (set == NULL)
        return ((char *)s1);
    start = 0;
    end = ft_strlen(s1);
    while (s1[start] && (ft_strchr(set, s1[start]) || s1[start] == ' '))
        start++;
    while (end > start && (ft_strchr(set, s1[end - 1]) || s1[end - 1] == ' '))
        end--;
    buffer = (char *)malloc(end - start + 1);
    if (!buffer)
        return (NULL);
    i = 0;
    while (start < end)
        buffer[i++] = s1[start++];
    buffer[i] = '\0';
    return (buffer);
}
