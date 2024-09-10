/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstaali <mstaali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:34:46 by mstaali           #+#    #+#             */
/*   Updated: 2024/09/10 18:46:44 by mstaali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_map_character(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E' || c == ' '
		|| c == '\n' || c == '\t')
		return (1);
	return (0);
}

void	is_map_valid(char *line)
{
	int	i;
	int	texture;

	if (!line)
	{
		error_mssg(EMPTY_FILE);
		exit(EXIT_FAILURE);
	}
	i = 0;
	texture = 0;
	while (line[i] && texture < 6)
	{
		if (line[i] == '\n' && line[i + 1] != '\n')
			texture++;
		i++;
	}
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			error_mssg(NEWLINE_MAP);
		if (!is_map_character(line[i]))
			error_mssg(MAP_CHAR);
		i++;
	}
}

void	get_layout(char *av)
{
	int		fd;
	char	*line;
	char	*to_free;
	char	**layout;
	char	*tmp;

	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	tmp = get_next_line(fd);
	while (tmp)
	{
		to_free = line;
		line = ft_strjoin(line, tmp);
		free(to_free);
		free(tmp);
		tmp = get_next_line(fd);
	}
	is_map_valid(line);
	layout = ft_split(line, '\n');
}
