/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:45:05 by aech-chi          #+#    #+#             */
/*   Updated: 2025/04/27 14:34:54 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	count_fasila(char *rgb_str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (rgb_str && rgb_str[i])
	{
		if (rgb_str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	valid_rgb(char *rgb_str)
{
	char	*str_copy;
	char	*token;
	int		count;

	count = count_fasila(rgb_str);
	if ((!rgb_str) || ((rgb_str[0] == ',')
			|| (rgb_str[ft_strlen(rgb_str) - 1] == ',')) || (count > 2))
		return (1);
	str_copy = ft_strdup(rgb_str);
	if (!str_copy)
		return (1);
	token = ft_strtok(str_copy, ",");
	count = 0;
	while (token)
	{
		if (is_valid_number(token))
			return (free(str_copy), 1);
		count++;
		token = ft_strtok(NULL, ",");
	}
	free(str_copy);
	if (count != 3)
		return (1);
	return (0);
}

int	is_valid_number(const char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (1);
		i++;
	}
	num = ft_atoi(str);
	if (num < 0 || num > 255)
		return (1);
	return (0);
}

static void	process_rgb_values(t_data *data, char **rgb, bool is_floor)
{
	if (is_floor)
	{
		data->r_f = ft_atoi(rgb[0]);
		data->g_f = ft_atoi(rgb[1]);
		data->b_f = ft_atoi(rgb[2]);
	}
	else
	{
		data->r_c = ft_atoi(rgb[0]);
		data->g_c = ft_atoi(rgb[1]);
		data->b_c = ft_atoi(rgb[2]);
	}
}

static void	parse_rgb_string(t_data *data, char *rgb_str, bool is_floor)
{
	char	**rgb;
	int		i;

	if (!rgb_str)
		return ;
	rgb = ft_split(rgb_str, ',');
	if (!rgb)
		return ;
	if (rgb[0] && rgb[1] && rgb[2] && !rgb[3])
		process_rgb_values(data, rgb, is_floor);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

void	set_rgb(t_data *data)
{
	parse_rgb_string(data, data->F, true);
	parse_rgb_string(data, data->C, false);
}
