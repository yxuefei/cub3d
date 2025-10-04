/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:00:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 11:23:08 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	assign_tex(char **dst, const char *line_after_id)
{
	char	*p;

	if (*dst)
		return (-1);
	p = parse_texture_path(line_after_id);
	if (!p)
		return (-1);
	*dst = p;
	return (1);
}

static int	parse_header_line(t_cub_data *d, const char *line)
{
	if (starts_with_id(line, "NO"))
		return (assign_tex(&d->no, line + 2));
	if (starts_with_id(line, "SO"))
		return (assign_tex(&d->so, line + 2));
	if (starts_with_id(line, "WE"))
		return (assign_tex(&d->we, line + 2));
	if (starts_with_id(line, "EA"))
		return (assign_tex(&d->ea, line + 2));
	if (starts_with_id(line, "F"))
	{
		if (d->floor_color != -1)
			return (-1);
		if (set_floor_color_from_line(d, line))
			return (1);
		return (-1);
	}
	if (starts_with_id(line, "C"))
	{
		if (d->ceiling_color != -1)
			return (-1);
		if (set_ceiling_color_from_line(d, line))
			return (1);
		return (-1);
	}
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
