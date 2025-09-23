/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:24:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/23 22:21:50 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	get_map_height(char **map)
{
	int	count;

	if (!map)
		return (0);
	count = 0;
	while (map[count])
		count++;
	return (count);
}

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
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

char	*parse_texture_path(const char *s)
{
	int		i;
	int		start;
	int		end;
	int		fd;
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
	if (!path)
		return (NULL);
	if ((int)ft_strlen(path) < 4 || ft_strncmp(path + strlen(path) - 4, ".xpm", 4) != 0)
	{
		free(path);
		return (NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

void	init_data(t_cub_data *d)
{
	if (!d)
		return ;
	d->no = NULL;
	d->so = NULL;
	d->we = NULL;
	d->ea = NULL;
	d->floor_color = -1;
	d->ceiling_color = -1;
	d->map = NULL;
	d->player_x = -1;
	d->player_y = -1;
	d->player_dir = '\0';
	d->mlx = NULL;
	d->win = NULL;
}

void	free_data(t_cub_data *d)
{
	int	i;

	if (!d)
		return ;
	free(d->no);
	free(d->so);
	free(d->we);
	free(d->ea);
	d->no = NULL;
	d->so = NULL;
	d->we = NULL;
	d->ea = NULL;
	if (d->map)
	{
		i = 0;
		while (d->map[i])
		{
			free(d->map[i]);
			i++;
		}
		free(d->map);
		d->map = NULL;
	}
}