/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_is_last.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:07:11 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 18:18:37 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	is_blank_char(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

static int	is_blank_line(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (!is_blank_char((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_map_is_last(char **lines, int map_end)
{
	int	i;

	if (!lines || map_end < 0)
		return (printf("Error: map is not the last"), 0);
	i = map_end;
	while (lines[i])
	{
		if (!is_blank_line(lines[i]))
			return (printf("Error: map is not the last"), 0);
		i++;
	}
	return (1);
}
