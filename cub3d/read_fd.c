#include "head.h"

static int	process_configuration_phase(char *line, t_data *data, bool *configs_done)
{
	if (is_empty_line(line))
		return (0);
	if (process_config_line(line, data))
		return (1);
	if (data->no && data->so && data->we && data->ea && data->F && data->C)
		*configs_done = true;
	return (0);
}

static int	process_map_phase(char *line, t_data *data)
{
	if (store_raw_map_line(line, data))
		return (1);
	return (0);
}

static int	process_line(char *line, t_data *data, bool *configs_done)
{
	if (!*configs_done)
	{
		if (process_configuration_phase(line, data, configs_done))
			return (1);
	}
	else
	{
		if (process_map_phase(line, data))
			return (1);
	}
	return (0);
}

int	read_file(char *filename, t_data *data, int fd)
{
	char	*line;
	bool	configs_done;

	configs_done = false;
	fd = open_file(filename, -1);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)))
	{
		if (process_line(line, data, &configs_done))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}
