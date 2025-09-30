/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:11:32 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/30 14:42:52 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

static void	skip_ws(const char *s, int *i)
{
	while (s[*i] && is_blank((unsigned char)s[*i]))
		(*i)++;
}

static int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	skip_ws(s, &i);
	return (s[i] == '0' || s[i] == '1');
}

int	find_map_range(char **lines, int *start, int *end)
{
	int	i;

	if (!lines || !start || !end)
		return (0);
	i = 0;
	while (lines[i] && !is_map_line(lines[i]))
		i++;
	if (!lines[i])
		return (0);
	*start = i;
	while (lines[i] && is_map_line(lines[i]))
		i++;
	*end = i;
	return (1);
}

char	**create_game_map(char **lines, int start, int end)
{
	char	**map;
	int		h;
	int		i;
	int		len;

	if (!lines || start < 0 || end < start)
		return (NULL);
	h = end - start;
	map = (char **)malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < h)
	{
		len = 0;
		while (lines[start + i][len] && lines[start + i][len] != '\n')
			len++;
		map[i] = ft_substr(lines[start + i], 0, len);
		if (!map[i])
		{
			map[i] = NULL;
			free_lines(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}
