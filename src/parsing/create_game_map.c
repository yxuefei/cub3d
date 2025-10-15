/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:11:32 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 18:23:53 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	find_map_range(char **lines, int *start, int *end)
{
	int	i;

	if (!lines || !start || !end)
		return (0);
	i = 0;
	while (lines[i] && !is_map_line(lines[i]))
		i++;
	if (!lines[i])
		return (printf("Error: no map found"), 0);
	*start = i;
	while (lines[i] && is_map_line(lines[i]))
		i++;
	*end = i;
	return (1);
}

static char	*dup_line(char *src)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != '\n')
		len++;
	return (ft_substr(src, 0, len));
}

char	**create_game_map(char **lines, int start, int end)
{
	char	**map;
	int		h;
	int		i;

	if (!lines || start < 0 || end < start)
		return (NULL);
	h = end - start;
	map = (char **)malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < h)
	{
		map[i] = dup_line(lines[start + i]);
		if (!map[i])
		{
			free_lines(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}
