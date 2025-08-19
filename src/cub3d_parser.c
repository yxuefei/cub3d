#include "../include/cub.h"

static void parse_texture(t_cub_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->no = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->so = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->we = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->ea = ft_strdup(line + 3);
	else
		error_general("Invalid texture line");
}

void	ft_free_split(char **str)
{
	int i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void parse_color(int *color, char *line)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(line + 2, ',');
	if (!parts || !parts[0] || ! parts[1] || !parts[2])
		error_general("Invalid color format");
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_general("Color out of range");
	*color = (r << 16) | (g << 8) | b;
	ft_free_split(parts);
}

static void append_map_line(t_cub_data *data, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (data->map && data->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		error_general("malloc");
	i = 0;
	while (data->map && data->map[i])
	{
		new_map[i] = data->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	if (data->map)
		free(data->map);
	data->map = new_map;
}

static void	find_player(t_cub_data *data)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (data->map && data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				if (found)
					error_general("multiple player positions");
				data->player_x = j;
				data->player_y = i;
				data->player_dir = data->map[i][j];
				data->map[i][j] = '0';
				found = 1;
			}
			j++;
		}
		i++;
	}
	if (!found)
		error_general("player not found");
}


static void	validate_map(t_cub_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (data->map && data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			if (c == '0')
			{
				if (i == 0 || data->map[i + 1] == NULL ||
                    j == 0 || data->map[i][j + 1] == '\0' ||
                    data->map[i-1][j] == ' ' || data->map[i+1][j] == ' ' ||
                    data->map[i][j-1] == ' ' || data->map[i][j+1] == ' ')
                {
                    error_general("map not closed");
                }
			}
			j++;
		}
		i++;
	}
}

t_cub_data *parse_cub_file(const char *filename)
{
	int			fd;
	char		*line;
	t_cub_data	*data;

	data = ft_calloc(1, sizeof(t_cub_data));
	if (!data)
		error_general("malloc");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_general("open");
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			parse_texture(data, line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color(&data->ceiling_color, line);
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color(&data->floor_color, line);
		else if (line[0] != '\n')
			append_map_line(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	find_player(data);
	validate_map(data);
	return (data);
}