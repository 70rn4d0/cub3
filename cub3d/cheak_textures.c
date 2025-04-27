/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheak_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:53:25 by aech-chi          #+#    #+#             */
/*   Updated: 2025/04/27 11:53:32 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	file_extension(char *av, bool c)
{
	char	*ext;

	ext = ft_strrchr(av, '.');
	if (ext == NULL)
		return (1);
	if (c == 0)
	{
		if (ft_strcmp(ext, ".cub") != 0)
			return (1);
	}
	if (c == 1)
	{
		if (ft_strcmp(ext, ".xpm") != 0)
			return (1);
	}
	return (0);
}

int	file_permission(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	open_file(char *map, int fd)
{
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (1);
	return (fd);
}

int	ft_wordcount(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ' || *str == '\t')
			in_word = 0;
		str++;
	}
	return (count);
}

int	texture_permission(t_data *data)
{
	if (ft_wordcount(data->so) != 1 || ft_wordcount(data->no) != 1
		|| ft_wordcount(data->we) != 1 || ft_wordcount(data->ea) != 1)
		return (2);
	if (file_permission(data->no))
		return (3);
	if (file_permission(data->ea))
		return (4);
	if (file_permission(data->so))
		return (5);
	if (file_permission(data->we))
		return (6);
	return (0);
}
