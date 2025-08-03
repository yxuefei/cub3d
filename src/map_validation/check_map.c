/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:18:23 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/03 15:37:52 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	check_map_rectangle(t_game *game, char **map)
{
	int	cur_col;
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
			j++;
		cur_col = j;
		if (cur_col != game->map->columns)
			error_read_map("map error: not rectangle", game);
		i++;
	}
}

static void	check_map_element(t_game *game)
{
	if (game->map->player_num != 1)
		error_read_map("map error: not single player", game);
	if (game->map->exit_num != 1)
		error_read_map("map error: not single exit", game);
	if (game->map->collect_num < 1)
		error_read_map("map error: not enough collectible", game);
}

static void	check_map_wall(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if ((i == 0 || i == game->map->rows - 1) && map[i][j] != WALL)
				error_read_map("map error: not wall surrounded", game);
			if ((j == 0 || j == game->map->columns - 1) && map[i][j] != WALL)
				error_read_map("map error: not wall surrounded", game);
			j++;
		}
		i++;
	}
}

static void	check_key(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (map[i][j] != PLAYER && map[i][j] != EXIT && \
				map[i][j] != COLLECT && map[i][j] != '1' && \
				map[i][j] != '0')
				error_read_map("map error: wrong key", game);
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game, char **map)
{
	check_map_rectangle(game, map);
	check_map_element(game);
	check_map_wall(game, map);
	check_key(game, map);
	is_valid_map(game, map, game->player->y, game->player->x);
}
