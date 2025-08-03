/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_filling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:12:44 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/03 15:37:49 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static char	**double_arr_copy(t_game *game, char **map)
{
	char	**map_copy;
	int		i;

	map_copy = malloc((game->map->rows + 1) * sizeof(char *));
	i = 0;
	while (i < game->map->rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
			error_read_map("malloc error: dup map", game);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (x < 0 || x >= game->map->rows || y < 0 || map_copy[x][y] == 'V'\
		|| y >= game->map->columns || map_copy[x][y] == WALL)
		return ;
	if (map_copy[x][y] == COLLECT)
		game->reach_collect++;
	if (map_copy[x][y] == EXIT)
		game->reach_exit++;
	map_copy[x][y] = 'V';
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
}

void	is_valid_map(t_game *game, char **map, int p_y, int p_x)
{
	char	**map_copy;

	map_copy = double_arr_copy(game, map);
	flood_fill(game, map_copy, p_y, p_x);
	free_array(map_copy);
	if (game->reach_collect != game->map->collect_num || game->reach_exit != 1)
		error_read_map("map error: not valid", game);
}
