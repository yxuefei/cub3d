/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:01:14 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/03 15:39:29 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_img	*init_img(t_game *game)
{
	t_img		*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		free(game->mlx);
		error_free_map("malloc error: img struct", game);
	}
	img->collect_img = process_png(PNG_COLLECT, game);
	img->exit_img = process_png(PNG_EXIT, game);
	img->player_img = process_png(PNG_PLAYER, game);
	img->floor_img = process_png(PNG_FLOOR, game);
	img->wall_img = process_png(PNG_WALL, game);
	return (img);
}

void	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(IMG_WIDTH * game->map->columns, \
		IMG_HEIGHT * game->map->rows, "so_long", true);
	if (!game->mlx)
		error_free_map("mlx init error", game);
}

t_map	*init_map(t_game *game)
{
	t_map		*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		free(game);
		error_general("malloc error: failed to create map struct");
	}
	ft_memset(map, 0, sizeof(t_map));
	game->map = map;
	return (map);
}

t_player	*init_player(t_game *game)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		free(game->map);
		free(game);
		error_general("malloc error: failed to create player struct");
	}
	ft_memset(player, 0, sizeof(t_player));
	game->player = player;
	return (player);
}

t_game	*init_game(char **av)
{
	t_game		*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_general("malloc error: failed to create game");
	game->map = init_map(game);
	game->real_map = NULL;
	game->player = init_player(game);
	game->fd = -1;
	game->count = 0;
	game->finish_game = 0;
	game->reach_collect = 0;
	game->reach_exit = 0;
	read_map(game, av[1]);
	init_mlx(game);
	game->img = init_img(game);
	game->enemy = init_enemy(game);
	return (game);
}
