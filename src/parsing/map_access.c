/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:29:03 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/30 14:33:08 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	row_len_upto_nl(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	map_height(char **map)
{
	int	h;

	if (!map)
		return (0);
	h = 0;
	while (map[h])
		h++;
	return (h);
}

char	map_at(t_cub_data *d, int x, int y)
{
	int	h;
	int	w;

	if (!d || !d->map)
		return ('1');
	h = map_height(d->map);
	if (y < 0 || y >= h)
		return ('1');
	w = row_len_upto_nl(d->map[y]);
	if (x < 0 || x >= w)
		return ('1');
	if (d->map[y][x] == ' ' || d->map[y][x] == '\t'
		|| d->map[y][x] == '\0' || d->map[y][x] == '\n')
		return ('1');
	return (d->map[y][x]);
}

int	map_is_wall(t_cub_data *d, double x, double y)
{
	int	grid_x;
	int	grid_y;
	char	c;

	grid_x = (int)x;
	grid_y = (int)y;
	c = map_at(d, grid_x, grid_y);
	return (c != '0');
}
