/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:11:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/01 16:41:50 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	set_dir_plane_ns(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0.0;  p->dir_y = -1.0;
		p->plane_x = 0.66; p->plane_y = 0.0;
	}
	else
	{
		p->dir_x = 0.0;  p->dir_y = 1.0;
		p->plane_x = -0.66; p->plane_y = 0.0;
	}
}

static void	set_dir_plane_ew(t_player *p, char dir)
{
	if (dir == 'E')
	{
		p->dir_x = 1.0;  p->dir_y = 0.0;
		p->plane_x = 0.0; p->plane_y = 0.66;
	}
	else
	{
		p->dir_x = -1.0;  p->dir_y = 0.0;
		p->plane_x = 0.0;  p->plane_y = -0.66;
	}
}

void	init_player_from_data(t_game *g)
{
	t_player	*p;

	p = &g->player;
	p->x = g->data->player_x + 0.5;
	p->y = g->data->player_y + 0.5;
	if (g->data->player_dir == 'N' || g->data->player_dir == 'S')
		set_dir_plane_ns(p, g->data->player_dir);
	else
		set_dir_plane_ew(p, g->data->player_dir);
}

t_cub_data *parse_cub_file(t_game *g, char *filename)
{
	t_cub_data *d;

	d = (t_cub_data *)malloc(sizeof(t_cub_data));
	if (!d)
		return (NULL);
	init_data(d);
	if (!load_and_parse(filename, d))
	{
		free_data(d);
		free(d);
		return (NULL);
	}
	g->data = d;
	init_player_from_data(g);
	return (d);
}
