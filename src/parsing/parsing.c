/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:43:05 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 19:16:00 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	fail_cleanup(char **lines, t_cub_data *d)
{
	if (lines)
		free_lines(lines);
	free_data(d);
	return (0);
}

int	parse_scene(char **lines, t_cub_data *d)
{
	int	i;
	int	r;
	int	s;
	int	e;

	if (!lines || !d)
		return (printf("Error: invalid parse input\n"), 0);
	i = 0;
	while (lines[i] && !is_map_line(lines[i]))
	{
		r = parse_header_line(d, lines[i]);
		if (r == -1)
			return (printf("Error: parse header\n"), 0);
		if (r == 0 && is_nonblank_line(lines[i]))
			return (printf("Error: unexpected blank line\n"), 0);
		i++;
	}
	if (!find_map_range(lines, &s, &e))
		return (0);
	d->map = create_game_map(lines, s, e);
	if (!d->map)
		return (printf("Error: map not created\n"), 0);
	if (!check_map_is_last(lines, e))
		return (0);
	return (1);
}

int	load_and_parse(char *path, t_cub_data *d)
{
	char	**lines;

	if (!path || !d)
		return (printf("Error: invalid input\n"), 0);
	if (!check_file(path))
		return (printf("Error: cub file\n"), 0);
	if (!load_cub_file(path, &lines))
		return (printf("Error: file reading\n"), 0);
	if (!parse_scene(lines, d))
		return (fail_cleanup(lines, d));
	free_lines(lines);
	if (!validate_textures(d))
		return (printf("Error: texture not valid\n"), fail_cleanup(NULL, d));
	if (!validate_map(d))
		return (fail_cleanup(NULL, d));
	return (1);
}
