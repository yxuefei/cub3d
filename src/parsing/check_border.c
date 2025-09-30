/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:02:24 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/30 16:06:56 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	effective_end(const char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i - 1);
}

int	check_top(char **map)
{
	int		j;
	char	*row;

	if (!map || !map[0])
		return (1);
	row = map[0];
	j = 0;
	while (row[j] && row[j] != '\n' && is_blank(row[j]))
		j++;
	if (!row[j] || row[j] == '\n')
		return (1);
	while (row[j] && row[j] != '\n')
	{
		if (row[j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_bottom(char **map, int map_height)
{
	int		j;
	char	*row;

	if (!map || map_height <= 0 || !map[map_height - 1])
		return (1);
	row = map[map_height - 1];
	j = 0;
	while (row[j] && row[j] != '\n' && is_blank(row[j]))
		j++;
	if (!row[j] || row[j] == '\n')
		return (1);
	while (row[j] && row[j] != '\n')
	{
		if (row[j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_left(char **map, int map_height)
{
	int		i;
	int		j;
	char	*row;

	if (!map || map_height < 3)
		return (1);
	i = 1;
	while (i < map_height - 1)
	{
		row = map[i];
		if (!row)
			return (1);
		j = 0;
		while (row[j] && row[j] != '\n' && is_blank(row[j]))
			j++;
		if (!row[j] || row[j] == '\n' || row[j] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_right(char **map, int map_height)
{
	int		i;
	int		end;
	char	*row;

	if (!map || map_height < 3)
		return (1);
	i = 1;
	while (i < map_height - 1)
	{
		row = map[i];
		if (!row)
			return (1);
		end = effective_end(row);
		if (end < 0)
			return (1);
		while (end >= 0 && is_blank(row[end]))
			end--;
		if (end < 0 || row[end] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_borders(char **map, int map_height)
{
	if (check_top(map))
		return (0);
	if (check_bottom(map, map_height))
		return (0);
	if (check_left(map, map_height))
		return (0);
	if (check_right(map, map_height))
		return (0);
	return (1);
}
