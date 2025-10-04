/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:24:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 10:46:11 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t'
		|| s[*i] == '\r' || s[*i] == '\n'
		|| s[*i] == '\v' || s[*i] == '\f')
		(*i)++;
}

static int	to_int(const char *s, int *i)
{
	int	val;

	val = 0;
	skip_spaces(s, i);
	if (!(s[*i] >= '0' && s[*i] <= '9'))
		return (-1);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		val = val * 10 + (s[*i] - '0');
		(*i)++;
	}
	skip_spaces(s, i);
	return (val);
}

/* "220, 100 ,0" -> 0xDC6400 */
int	parse_color_string(const char *s)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (!s)
		return (-1);
	i = 0;
	r = to_int(s, &i);
	if (r < 0 || s[i++] != ',')
		return (-1);
	g = to_int(s, &i);
	if (g < 0 || s[i++] != ',')
		return (-1);
	b = to_int(s, &i);
	if (b < 0)
		return (-1);
	skip_spaces(s, &i);
	if (s[i] != '\0')
		return (-1);
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (0);
	}
	close(fd);
	return (1);
}

char	*parse_texture_path(const char *s)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	if (!s)
		return (NULL);
	i = 0;
	skip_spaces(s, &i);
	start = i;
	while (s[i] && s[i] != '\n')
		i++;
	end = i;
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	path = ft_substr(s, start, end - start);
	if (!path || !is_valid_path(path))
		return (NULL);
	return (path);
}
