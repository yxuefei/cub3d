/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:02:24 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 10:53:30 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	check_top_border(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = first_noblank_idx(map[0]);
	if (i < 0)
		return (0);
	while (map[0][i])
	{
		if (!is_blank((unsigned char)map[0][i])
			&& map[0][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_bottom_border(char **map, int h)
{
	int	i;

	if (!map || h <= 0 || !map[h - 1])
		return (0);
	i = first_noblank_idx(map[h - 1]);
	if (i < 0)
		return (0);
	while (map[h - 1][i])
	{
		if (!is_blank((unsigned char)map[h - 1][i])
			&& map[h - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_left_border(char **map, int h)
{
	int	y;
	int	x;

	if (!map || h <= 0)
		return (0);
	y = 0;
	while (y < h)
	{
		x = first_noblank_idx(map[y]);
		if (x < 0)
			return (0);
		if (map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_right_border(char **map, int h)
{
	int	y;
	int	x;

	if (!map || h <= 0)
		return (0);
	y = 0;
	while (y < h)
	{
		x = last_noblank_idx(map[y]);
		if (x < 0)
			return (0);
		if (map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_borders(char **map, int h)
{
	if (!check_top_border(map))
		return (0);
	if (!check_bottom_border(map, h))
		return (0);
	if (!check_left_border(map, h))
		return (0);
	if (!check_right_border(map, h))
		return (0);
	return (1);
}
