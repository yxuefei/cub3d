/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:35:56 by omalovic          #+#    #+#             */
/*   Updated: 2025/10/16 13:37:05 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	load_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->data->no;
	paths[1] = game->data->so;
	paths[2] = game->data->we;
	paths[3] = game->data->ea;
	i = 0;
	while (i < 4)
	{
		game->tex[i].tex = mlx_load_png(paths[i]);
		if (!game->tex[i].tex)
			error_general("failed to load texture");
		game->tex[i].width = game->tex[i].tex->width;
		game->tex[i].height = game->tex[i].tex->height;
		i++;
	}
}

int	select_texture(t_ray *ray, int side)
{
	if (side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SO);
		else
			return (NO);
	}
}
