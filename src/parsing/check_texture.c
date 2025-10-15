/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:38:47 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 17:48:42 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	check_file_exists(char *path)
{
	int		fd;
	int		len;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	len = (int)ft_strlen(path);
	if (len < 4)
		return (0);
	if (!is_png_file(path))
		return (0);
	return (1);
}

int	validate_textures(t_cub_data *d)
{
	if (!d || !d->no || !d->so || !d->we || !d->ea)
		return (0);
	if (!check_file_exists(d->no))
		return (0);
	if (!check_file_exists(d->so))
		return (0);
	if (!check_file_exists(d->we))
		return (0);
	if (!check_file_exists(d->ea))
		return (0);
	if (d->floor_color < 0 || d->floor_color > 0xFFFFFF)
		return (0);
	if (d->ceiling_color < 0 || d->ceiling_color > 0xFFFFFF)
		return (0);
	return (1);
}
