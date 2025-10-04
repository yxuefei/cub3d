/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_and_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 10:42:28 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 11:08:56 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

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
