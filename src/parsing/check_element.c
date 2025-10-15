/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:21:30 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/14 09:55:45 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

static int	is_allowed_cell(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| is_blank(c) || c == '\n' || c == '\0');
}

static int	process_cell(t_cub_data *d, int y, int x, int *pc)
{
	char	c;

	c = d->map[y][x];
	if (!is_allowed_cell(c))
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		d->player_y = y;
		d->player_x = x;
		d->player_dir = c;
		(*pc)++;
	}
	return (1);
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
			if (!process_cell(d, y, x, &player_cnt))
				return (0, printf("Error: wrong elements"));
			x++;
		}
		y++;
	}
	if (player_cnt == 1)
		return (0, printf("Error: wrong number of player"));
	return (1);
}
