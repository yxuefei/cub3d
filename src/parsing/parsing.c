/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:43:05 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/01 15:59:41 by xueyang          ###   ########.fr       */
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

int	load_and_parse(char *path, t_cub_data *d)
{
	char	**lines;

	if (!path || !d)
		return (0);
	if (!check_file(path))
		return (0);
	if (!load_cub_file(path, &lines))
		return (0);
	if (!parse_scene(lines, d))
		return (fail_cleanup(lines, d));
	free_lines(lines);
	if (!validate_textures(d))
		return (fail_cleanup(NULL, d));
	if (!validate_map(d))
		return (fail_cleanup(NULL, d));
	return (1);
}
