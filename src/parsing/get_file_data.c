/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:00:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 13:38:31 by xueyang          ###   ########.fr       */
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

static int	handle_tex(const char *line, const char *id, char **dst)
{
	const char	*p;

	p = after_id_ptr(line, id);
	if (!p)
		return (0);
	if (*dst)
		return (-1);
	return (assign_tex(dst, p));
}

static int	handle_floor(t_cub_data *d, const char *line)
{
	const char	*p;

	p = after_id_ptr(line, "F");
	if (!p)
		return (0);
	if (d->floor_color != -1)
		return (-1);
	if (!set_floor_color_from_line(d, p))
		return (-1);
	return (1);
}

static int	handle_ceiling(t_cub_data *d, const char *line)
{
	const char	*p;

	p = after_id_ptr(line, "C");
	if (!p)
		return (0);
	if (d->ceiling_color != -1)
		return (-1);
	if (!set_ceiling_color_from_line(d, p))
		return (-1);
	return (1);
}

int	parse_header_line(t_cub_data *d, const char *line)
{
	int	r;

	r = handle_tex(line, "NO", &d->no);
	if (r)
		return (r);
	r = handle_tex(line, "SO", &d->so);
	if (r)
		return (r);
	r = handle_tex(line, "WE", &d->we);
	if (r)
		return (r);
	r = handle_tex(line, "EA", &d->ea);
	if (r)
		return (r);
	r = handle_floor(d, line);
	if (r)
		return (r);
	r = handle_ceiling(d, line);
	if (r)
		return (r);
	return (0);
}
