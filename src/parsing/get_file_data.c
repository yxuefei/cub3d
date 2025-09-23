/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:00:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/23 19:18:31 by xueyang          ###   ########.fr       */
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

static int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	skip_ws(s, &i);
	return (s[i] == '0' || s[i] == '1');
}

static int	is_nonblank_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_blank_char((unsigned char)s[i]) && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
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
	int	r;
	int	s;
	int	e;

	if (!lines || !d)
		return (0);
	i = 0;
	while (lines[i] && !is_map_line(lines[i]))
	{
		r = parse_header_line(d, lines[i]);
		if (r == -1)
			return (0);
		if (r == 0 && is_nonblank_line(lines[i]))
			return (0);
		i++;
	}
	if (!find_map_range(lines, &s, &e))
		return (0);
	d->map = create_game_map(lines, s, e);
	if (!d->map)
		return (0);
	if (!check_map_is_last(lines, e))
		return (0);
	return (1);
}
