/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:21:30 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/30 16:05:10 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_allowed_cell(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| is_blank(c) || c == '\n' || c == '\0');
}

int	check_map_elements(t_cub_data *d)
{
	int	y;
	int	x;
	int	player_cnt;

	if (!d || !d->map)
		return (0);
	player_cnt = 0;
	y = 0;
	while (d->map[y])
	{
		x = 0;
		while (d->map[y][x] && d->map[y][x] != '\n')
		{
			if (!is_allowed_cell(d->map[y][x]))
				return (0);
			if (d->map[y][x] == 'N' || d->map[y][x] == 'S'
				|| d->map[y][x] == 'E' || d->map[y][x] == 'W')
			{
				d->player_y = y;
				d->player_x = x;
				d->player_dir = d->map[y][x];
				player_cnt++;
			}
			x++;
		}
		y++;
	}
	return (player_cnt == 1);
}
