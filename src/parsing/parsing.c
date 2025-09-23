/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:43:05 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/23 19:27:36 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

//needs to be changed to free_all_data
static void	free_cub_data_partial(t_cub_data *d)
{
	int	i;

	if (!d)
		return ;
	free(d->no);
	free(d->so);
	free(d->we);
	free(d->ea);
	d->no = NULL;
	d->so = NULL;
	d->we = NULL;
	d->ea = NULL;
	if (d->map)
	{
		i = 0;
		while (d->map[i])
		{
			free(d->map[i]);
			i++;
		}
		free(d->map);
		d->map = NULL;
	}
}

static int	fail_cleanup(char **lines, t_cub_data *d)
{
	if (lines)
		free_lines(lines);
	free_cub_data_partial(d);
	return (0);
}

int	load_and_parse(const char *path, t_cub_data *d)
{
	char	**lines;

	if (!path || !d)
		return (0);
	if (!check_cub_path(path))
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
