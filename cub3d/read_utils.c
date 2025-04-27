/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:01:03 by aech-chi          #+#    #+#             */
/*   Updated: 2025/04/27 14:01:27 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_strtrim_end(char const *s, char const *set)
{
	char	*end;

	if (!s || !set)
		return (NULL);
	end = (char *)s + ft_strlen(s) - 1;
	while (end >= s && ft_strchr(set, *end))
		end--;
	return (ft_substr(s, 0, end - s + 1));
}

int	store_raw_map_line(char *line, t_data *data)
{
	char	**new_map;
	int		i;

	new_map = malloc((data->map_height + 2) * sizeof(char *));
	if (!new_map)
		return (1);
	i = -1;
	while (++i < data->map_height)
		new_map[i] = data->map[i];
	new_map[data->map_height] = ft_strdup(line);
	new_map[data->map_height + 1] = NULL;
	free(data->map);
	data->map = new_map;
	data->map_height++;
	if ((int)ft_strlen(line) > data->map_width)
		data->map_width = ft_strlen(line);
	return (0);
}
