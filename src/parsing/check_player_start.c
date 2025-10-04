/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:30:22 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 12:26:21 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	safe_cell(char c)
{
	if (c == '\0' || c == '\n')
		return (0);
	return (1);
}

int	fix_and_validate_player_pos(t_cub_data *d)
{
	int	h;
	int	x;
	int	y;

	if (!d || !d->map)
		return (0);
	y = d->player_y;
	x = d->player_x;
	h = get_map_height(d->map);
	if (y <= 0 || y >= h - 1)
		return (0);
	if (row_len_upto_nl(d->map[y - 1]) <= x
		|| row_len_upto_nl(d->map[y + 1]) <= x)
		return (0);
	if (x <= 0 || row_len_upto_nl(d->map[y]) <= x + 1)
		return (0);
	if (!safe_cell(d->map[y - 1][x]) || !safe_cell(d->map[y + 1][x])
		|| !safe_cell(d->map[y][x - 1]) || !safe_cell(d->map[y][x + 1]))
		return (0);
	d->map[y][x] = '0';
	return (1);
}

// static char	cell_at(char **map, int y, int x)
// {
// 	int	h;
// 	int	w;

// 	h = 0;
// 	while (map && map[h])
// 		h++;
// 	if (y < 0 || y >= h)
// 		return (' ');
// 	w = row_len_upto_nl(map[y]);
// 	if (x < 0 || x >= w)
// 		return (' ');
// 	return (map[y][x]);
// }

static int	is_oob(char **map, int y, int x)
{
	int	h;
	int	w;

	h = 0;
	while (map && map[h])
		h++;
	if (y < 0 || y >= h)
		return (1);
	w = row_len_upto_nl(map[y]);
	if (x < 0 || x >= w)
		return (1);
	return (0);
}

static int	is_open_adjacent(char **map, int y, int x)
{
	return (is_oob(map, y - 1, x)
		|| is_oob(map, y + 1, x)
		|| is_oob(map, y, x - 1)
		|| is_oob(map, y, x + 1));
}

int	check_open_tiles_closed(char **map)
{
	int	y;
	int	x;
	int	h;
	int	w;

	if (!map)
		return (0);
	h = 0;
	while (map[h])
		h++;
	y = 0;
	while (y < h)
	{
		w = row_len_upto_nl(map[y]);
		x = 0;
		while (x < w)
		{
			if (map[y][x] == '0' && is_open_adjacent(map, y, x))
				return (0);
			else
				x++;
		}
		y++;
	}
	return (1);
}
