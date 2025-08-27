#include "../include/cub.h"

static void check_cub_extension(const char *filename)
{
    int len = ft_strlen(filename);
    if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
        error_general("invalid file extension");
}

static void parse_texture(t_cub_data *data, char *line)
{
    char *trimmed = ft_strtrim(line, " \t\n");
    char *path;

    if (ft_strncmp(trimmed, "NO", 2) == 0)
        path = ft_strtrim(trimmed + 2, " \t\n"), data->no = path;
    else if (ft_strncmp(trimmed, "SO", 2) == 0)
        path = ft_strtrim(trimmed + 2, " \t\n"), data->so = path;
    else if (ft_strncmp(trimmed, "WE", 2) == 0)
        path = ft_strtrim(trimmed + 2, " \t\n"), data->we = path;
    else if (ft_strncmp(trimmed, "EA", 2) == 0)
        path = ft_strtrim(trimmed + 2, " \t\n"), data->ea = path;
    else
    {
        free(trimmed);
        error_general("invalid texture line");
    }
    free(trimmed);
}

void ft_free_split(char **str)
{
    int i;

    if (!str)
        return;
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
    char **parts;
    int r, g, b;
    char *trimmed;

    trimmed = ft_strtrim(line + 1, " \t\n"); // пропускаем F или C
    parts = ft_split(trimmed, ',');
    free(trimmed);

    if (!parts || !parts[0] || !parts[1] || !parts[2])
        error_general("invalid color format");

    r = ft_atoi(parts[0]);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        error_general("color out of range");

    *color = r * 65536 + g * 256 + b; // 0xRRGGBB
    ft_free_split(parts);
}

static void append_map_line(t_cub_data *data, char *line)
{
    char **new_map;
    int i;

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

    // удаляем символ \n в конце строки
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    new_map[i] = ft_strdup(line);
    new_map[i + 1] = NULL;

    if (data->map)
        free(data->map);
    data->map = new_map;
}

static void find_player(t_cub_data *data)
{
    int i, j;
    int found = 0;

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

static void validate_map(t_cub_data *data)
{
    int i = 0;
    int j;
    int height = 0;
    int width;

    if (!data->map || !data->map[0])
        error_general("empty map");

    // считаем высоту карты
    while (data->map[height])
        height++;

    width = ft_strlen(data->map[0]);

    while (i < height)
    {
        // проверка прямоугольности
        if ((int)ft_strlen(data->map[i]) != width)
            error_general("map is not rectangular");

        j = 0;
        while (j < width)
        {
            char c = data->map[i][j];

            // проверка допустимых символов
            if (c != '0' && c != '1' && c != ' ')
                error_general("invalid character in map");

            // проверка замкнутости для пустой клетки
            if (c == '0')
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    error_general("map not closed");

                if (data->map[i-1][j] == ' ' || data->map[i+1][j] == ' ' ||
                    data->map[i][j-1] == ' ' || data->map[i][j+1] == ' ')
                    error_general("map not closed");
            }
            j++;
        }
        i++;
    }
}

static void check_duplicates(t_cub_data *data, char *id)
{
    if ((ft_strncmp(id, "NO", 2) == 0 && data->no) ||
        (ft_strncmp(id, "SO", 2) == 0 && data->so) ||
        (ft_strncmp(id, "WE", 2) == 0 && data->we) ||
        (ft_strncmp(id, "EA", 2) == 0 && data->ea) ||
        (ft_strncmp(id, "F", 1) == 0 && data->floor_color != -1) ||
        (ft_strncmp(id, "C", 1) == 0 && data->ceiling_color != -1))
        error_general("duplicate identifier");
}

t_cub_data *parse_cub_file(const char *filename)
{
    int fd;
    char *line;
    int map_started = 0;
    t_cub_data *data;

    check_cub_extension(filename);

    data = ft_calloc(1, sizeof(t_cub_data));
    if (!data)
        error_general("malloc");
    data->floor_color = -1;
    data->ceiling_color = -1;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_general("open");

    line = get_next_line(fd);
    while (line)
    {
        char *trimmed = ft_strtrim(line, " \t\n");

        if (!map_started &&
            (ft_strncmp(trimmed, "NO", 2) == 0 || ft_strncmp(trimmed, "SO", 2) == 0 ||
             ft_strncmp(trimmed, "WE", 2) == 0 || ft_strncmp(trimmed, "EA", 2) == 0))
        {
            if (ft_strncmp(trimmed, "NO", 2) == 0) check_duplicates(data, "NO");
            else if (ft_strncmp(trimmed, "SO", 2) == 0) check_duplicates(data, "SO");
            else if (ft_strncmp(trimmed, "WE", 2) == 0) check_duplicates(data, "WE");
            else if (ft_strncmp(trimmed, "EA", 2) == 0) check_duplicates(data, "EA");
            parse_texture(data, line); // передаём оригинальную строку
        }
        else if (!map_started && ft_strncmp(trimmed, "C", 1) == 0)
        {
            check_duplicates(data, "C");
            parse_color(&data->ceiling_color, line);
        }
        else if (!map_started && ft_strncmp(trimmed, "F", 1) == 0)
        {
            check_duplicates(data, "F");
            parse_color(&data->floor_color, line);
        }
        else if (trimmed[0] != '\0')
        {
            map_started = 1;
            append_map_line(data, line); // оригинальная строка
        }
        else if (map_started && trimmed[0] == '\0')
        {
            free(trimmed);
            free(line);
            error_general("empty line inside map");
        }

        free(trimmed);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);

    if (!data->no || !data->so || !data->we || !data->ea ||
        data->floor_color == -1 || data->ceiling_color == -1)
        error_general("missing identifier");

    find_player(data);
    validate_map(data);

    return data;
}

// t_cub_data *parse_cub_file(const char *filename)
// {
// 	int			fd;
// 	char		*line;
// 	t_cub_data	*data;

// 	data = ft_calloc(1, sizeof(t_cub_data));
// 	if (!data)
// 		error_general("malloc");
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		error_general("open");
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
// 			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
// 			parse_texture(data, line);
// 		else if (ft_strncmp(line, "C ", 2) == 0)
// 			parse_color(&data->ceiling_color, line);
// 		else if (ft_strncmp(line, "F ", 2) == 0)
// 			parse_color(&data->floor_color, line);
// 		else if (line[0] != '\n')
// 			append_map_line(data, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	if (!data->no || !data->so || !data->we || !data->ea
//         || data->floor_color == -1 || data->ceiling_color == -1)
//         error_general("missing identifier");
// 	find_player(data);
// 	validate_map(data);
// 	return (data);
// }