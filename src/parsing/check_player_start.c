/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:30:22 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/23 00:31:27 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	row_len_upto_nl(char *s)
{
	int i = 0;
	if (!s) return 0;
	while (s[i] && s[i] != '\n')
		i++;
	return i;
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
	if (x <= 0 || row_len_upto_nl(d->map[y]) <= x + 0)
		return (0);
	if (!safe_cell(d->map[y - 1][x]) || !safe_cell(d->map[y + 1][x])
		|| !safe_cell(d->map[y][x - 1]) || !safe_cell(d->map[y][x + 1]))
		return (0);
	d->map[y][x] = '0';
	return (1);
}
