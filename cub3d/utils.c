/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:03:02 by aech-chi          #+#    #+#             */
/*   Updated: 2025/04/27 14:03:49 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

#include "head.h"

static char	*get_start_position(char *str, const char *delim, char **save_ptr)
{
	if (!str)
	{
		if (!*save_ptr)
			return (NULL);
		str = *save_ptr;
	}
	while (*str && ft_strchr(delim, *str))
		str++;
	if (!*str)
	{
		*save_ptr = NULL;
		return (NULL);
	}
	return (str);
}

static char	*find_token_end(char *str, const char *delim, char **save_ptr)
{
	char	*token;

	token = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		*save_ptr = str + 1;
	}
	else
	{
		*save_ptr = NULL;
	}
	return (token);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save_ptr = NULL;
	char		*start_pos;

	start_pos = get_start_position(str, delim, &save_ptr);
	if (!start_pos)
		return (NULL);
	return (find_token_end(start_pos, delim, &save_ptr));
}

int	check_player_count(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (ft_strchr("NSEW", data->map[i][j]))
			{
				data->player_dir = data->map[i][j];
				player_count++;
			}
		}
	}
	if (player_count != 1)
	{
		printf("Error: Found %d players (expected 1)\n", player_count);
		return (1);
	}
	return (0);
}

int	hexa_color(t_data *data)
{
	if (data->C == NULL)
		return (1);
	if (valid_rgb(data->C))
		return (1);
	if (valid_rgb(data->F))
		return (1);
	set_rgb(data);
	return (0);
}
