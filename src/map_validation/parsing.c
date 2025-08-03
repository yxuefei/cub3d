/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:12:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/03/08 17:53:21 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_map(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->real_map[i] = ft_strdup(line);
		free(line);
		if (!game->real_map[i])
			error_read_map("malloc error: filling map", game);
		i++;
		line = get_next_line(fd);
		if (i > MAX_ROW)
		{
			free(line);
			error_read_map("malloc error: too big map, max row 100", game);
		}
	}
	game->real_map[i] = NULL;
}

static void	init_t_map(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j] != '\0')
		{
			if (map[i][j] == PLAYER)
			{
				game->map->player_num++;
				game->player->x = j;
				game->player->y = i;
			}
			if (map[i][j] == COLLECT)
				game->map->collect_num++;
			if (map[i][j] == EXIT)
				game->map->exit_num++;
			j++;
		}
		i++;
	}
	game->map->columns = j;
	game->map->rows = i;
}

void	read_map(t_game *game, char *filename)
{
	char	**map;

	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		error_general("open error: failed to open file");
	map = malloc(MAX_ROW * sizeof(char *));
	if (!map)
	{
		close(game->fd);
		free(game->map);
		free(game->player);
		free(game);
		error_general("malloc error: map reading");
	}
	game->real_map = map;
	ft_bzero(map, MAX_ROW * sizeof(char *));
	fill_map(game->fd, game);
	init_t_map(game, map);
	check_map(game, map);
	close(game->fd);
}
