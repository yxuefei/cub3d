/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:30:22 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/01 17:13:37 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	row_len_upto_nl(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	safe_cell(char c)
{
	if (c == '\0' || c == '\n' || c == ' ' || c == '\t')
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
	if (row_len_upto_nl(d->map[y - 1]) <= x || row_len_upto_nl(d->map[y + 1]) <= x)
		return (0);
	if (x <= 0 || row_len_upto_nl(d->map[y]) <= x + 1)
		return (0);
	if (!safe_cell(d->map[y - 1][x]) || !safe_cell(d->map[y + 1][x])
		|| !safe_cell(d->map[y][x - 1]) || !safe_cell(d->map[y][x + 1]))
		return (0);
	d->map[y][x] = '0';
	return (1);
}

// int	check_open_tiles_closed(char **map)
// {
// 	int	h;
// 	int	y;
// 	int	x;
// 	int	rowlen;

// 	if (!map)
// 		return (0);
// 	h = 0;
// 	while (map[h])
// 		h++;
// 	if (h < 3)
// 		return (0);
// 	y = 0;
// 	while (y < h)
// 	{
// 		rowlen = row_len_upto_nl(map[y]);
// 		x = 0;
// 		while (x < rowlen)
// 		{
// 			if (map[y][x] == '0')
// 			{
// 				if (y == 0 || y == h - 1)
// 					return (0);
// 				if (row_len_upto_nl(map[y - 1]) <= x
// 					|| row_len_upto_nl(map[y + 1]) <= x
// 					|| x == 0 || x + 1 >= rowlen)
// 					return (0);
// 				if (!safe_cell(map[y - 1][x]) || !safe_cell(map[y + 1][x])
// 					|| !safe_cell(map[y][x - 1]) || !safe_cell(map[y][x + 1]))
// 					return (0);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }

/* 取 (y,x) 的字符；越界/短行 返回 ' '（空气） */
static char	cell_at(char **map, int y, int x)
{
	int	h;
	int	w;

	h = 0;
	while (map && map[h])
		h++;
	if (y < 0 || y >= h)
		return (' ');
	w = row_len_upto_nl(map[y]);
	if (x < 0 || x >= w)
		return (' ');
	return (map[y][x]);
}

/* 空气（不允许紧贴）：空格/Tab/回车 等 */
static int	is_air(int c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

/* 核心：对每个 '0'，若任一四邻是“空气”，则不封闭 -> 返回 0 */
int	check_open_tiles_closed(char **map)
{
	int	y;
	int	x;
	int	h;
	int	w;

	h = 0;
	while (map && map[h])
		h++;
	y = 0;
	while (y < h)
	{
		w = row_len_upto_nl(map[y]);
		x = 0;
		while (x < w)
		{
			if (map[y][x] == '0')
			{
				if (is_air(cell_at(map, y - 1, x))
					|| is_air(cell_at(map, y + 1, x))
					|| is_air(cell_at(map, y, x - 1))
					|| is_air(cell_at(map, y, x + 1)))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
