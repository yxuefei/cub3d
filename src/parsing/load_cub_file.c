/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:51:12 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 11:09:11 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/* kinda realloc, expand the capacity */
static char	**grow_lines(char **arr, int *cap, int count)
{
	char	**new_arr;
	int		i;
	int		new_cap;

	new_cap = (*cap) * 2;
	new_arr = (char **)malloc(sizeof(char *) * new_cap);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	*cap = new_cap;
	return (new_arr);
}

static void	free_partial(char **arr, int n)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	ensure_cap(char ***arr, int *cap, int n, char *line)
{
	char	**tmp;

	if (n + 1 < *cap)
		return (1);
	tmp = grow_lines(*arr, cap, n);
	if (!tmp)
	{
		free(line);
		return (0);
	}
	*arr = tmp;
	return (1);
}

static int	read_all_lines(int fd, char ***out_lines)
{
	char	**arr;
	char	*line;
	int		cap;
	int		n;

	cap = 64;
	n = 0;
	arr = (char **)malloc(sizeof(char *) * cap);
	if (!arr)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ensure_cap(&arr, &cap, n, line))
		{
			free_partial(arr, n);
			return (0);
		}
		arr[n++] = line;
	}
	arr[n] = NULL;
	*out_lines = arr;
	return (1);
}

int	load_cub_file(const char *path, char ***out_lines)
{
	int	fd;
	int	ok;

	if (!path || !out_lines)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	ok = read_all_lines(fd, out_lines);
	close(fd);
	if (!ok)
		return (0);
	return (1);
}
