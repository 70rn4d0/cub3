/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:59:12 by aech-chi          #+#    #+#             */
/*   Updated: 2025/04/27 13:59:14 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int	store_configuration(char *key, char *value, t_data *data)
{
	if (ft_strcmp(key, "NO") == 0 && !data->no)
		data->no = ft_strdup(value);
	else if (ft_strcmp(key, "SO") == 0 && !data->so)
		data->so = ft_strdup(value);
	else if (ft_strcmp(key, "WE") == 0 && !data->we)
		data->we = ft_strdup(value);
	else if (ft_strcmp(key, "EA") == 0 && !data->ea)
		data->ea = ft_strdup(value);
	else if (ft_strcmp(key, "F") == 0 && !data->F)
		data->F = ft_strdup(value);
	else if (ft_strcmp(key, "C") == 0 && !data->C)
		data->C = ft_strdup(value);
	else
		return (1);
	return (0);
}

static int	extract_key(char *line, int *i, char **key)
{
	int	key_start;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	key_start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
		(*i)++;
	if (*i == key_start)
		return (1);
	*key = ft_substr(line, key_start, *i - key_start);
	return (0);
}

static int	extract_value(char *line, int *i, char **value)
{
	int	value_start;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	value_start = *i;
	while (line[*i] && line[*i] != '\n')
		(*i)++;
	while (*i > value_start && (line[*i - 1] == ' ' || line[*i - 1] == '\t'))
		(*i)--;
	if (*i == value_start)
		return (1);
	*value = ft_substr(line, value_start, *i - value_start);
	return (0);
}

static int	validate_remaining_chars(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && line[i] != '\n')
		return (1);
	return (0);
}

int	process_config_line(char *line, t_data *data)
{
	char	*key;
	char	*value;
	int		i;
	int		result;

	i = 0;
	if (extract_key(line, &i, &key))
		return (1);
	if (extract_value(line, &i, &value))
	{
		free(key);
		return (1);
	}
	if (validate_remaining_chars(line, i))
	{
		free(key);
		free(value);
		return (1);
	}
	result = store_configuration(key, value, data);
	free(key);
	free(value);
	return (result);
}
