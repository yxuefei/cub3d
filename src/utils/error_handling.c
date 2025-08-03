/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:13:16 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/03 15:37:33 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	error_general(char *msg)
{
	perror("Error\n");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_read_map(char *msg, t_game *game)
{
	close(game->fd);
	free_array(game->real_map);
	free(game->map);
	free(game->player);
	free(game);
	error_general(msg);
}

void	error_free_map(char *msg, t_game *game)
{
	free_array(game->real_map);
	free(game->map);
	free(game->player);
	free(game);
	error_general(msg);
}

void	error_free_all(char *msg, t_game *game)
{
	free_array(game->real_map);
	free(game->map);
	free(game->player);
	free(game->img);
	mlx_terminate(game->mlx);
	free(game);
	error_general(msg);
}

void	normal_exit(char *msg, t_game *game)
{
	free_array(game->real_map);
	free(game->map);
	free(game->player);
	free(game->img);
	mlx_terminate(game->mlx);
	ft_printf(msg);
	free(game);
	exit(EXIT_SUCCESS);
}
