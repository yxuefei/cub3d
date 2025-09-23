/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:00:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/23 01:09:41 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

static void	skip_ws(const char *s, int *i)
{
	while (s[*i] && is_blank((unsigned char)s[*i]))
		(*i)++;
}

static int	starts_with_id(const char *s, const char *id)
{
	int	i;
	int	k;

	i = 0;
	skip_ws(s, &i);
	k = 0;
	while (id[k])
	{
		if (s[i + k] != id[k])
			return (0);
		k++;
	}
	return (1);
}

static int	is_map_start_line(const char *s)
{
	int	i;

	i = 0;
	skip_ws(s, &i);
	if (s[i] == '0' || s[i] == '1')
		return (1);
	return (0);
}

static char	**dup_map(char **lines, int start, int end)
{
	char	**map;
	int		h;
	int		i;

	h = end - start;
	map = (char **)malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < h)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
			return (free_lines(map), NULL);
		i++;
	}
	map[i] = NULL;
	return (map);
}

static int	parse_header_line(t_cub_data *d, const char *line)
{
	if (starts_with_id(line, "NO"))
		return ((d->no = parse_texture_path(line + 2)) != NULL);
	if (starts_with_id(line, "SO"))
		return ((d->so = parse_texture_path(line + 2)) != NULL);
	if (starts_with_id(line, "WE"))
		return ((d->we = parse_texture_path(line + 2)) != NULL);
	if (starts_with_id(line, "EA"))
		return ((d->ea = parse_texture_path(line + 2)) != NULL);
	if (starts_with_id(line, "F"))
		return ((d->floor_color = parse_color_string(line + 1)) != -1);
	if (starts_with_id(line, "C"))
		return ((d->ceiling_color = parse_color_string(line + 1)) != -1);
	return (0);
}

int	parse_scene(char **lines, t_cub_data *d)
{
	int	i;
	int	map_s;
	int	map_e;

	if (!lines || !d)
		return (0);
	i = 0;
	while (lines[i] && !is_map_start_line(lines[i]))
	{
		if (*lines[i] != '\0' && *lines[i] != '\n')
			if (parse_header_line(d, lines[i]) == 0)
				;
		i++;
	}
	if (!lines[i] || !is_map_start_line(lines[i]))
		return (0);
	map_s = i;
	while (lines[i])
		i++;
	map_e = i;
	d->map = dup_map(lines, map_s, map_e);
	if (!d->map)
		return (0);
	if (!check_map_is_last(lines, map_e))
		return (0);
	return (1);
}