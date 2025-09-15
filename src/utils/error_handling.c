/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:13:16 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/16 00:54:25 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	error_general(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	//need to free stuff here
	exit(EXIT_FAILURE);
}

// void	free_array(char **str)
// {
// 	int i;

// 	if (!str)
// 		return ;
// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

// void	error_read_map(char *msg, t_game *game)
// {
// 	close(game->fd);
// 	free_array(game->real_map);
// 	free(game->map);
// 	free(game->player);
// 	free(game);
// 	error_general(msg);
// }

// void	error_free_map(char *msg, t_game *game)
// {
// 	free_array(game->real_map);
// 	free(game->map);
// 	free(game->player);
// 	free(game);
// 	error_general(msg);
// }

// void	error_free_all(char *msg, t_game *game)
// {
// 	free_array(game->real_map);
// 	free(game->map);
// 	free(game->player);
// 	free(game->img);
// 	mlx_terminate(game->mlx);
// 	free(game);
// 	error_general(msg);
// }

// void	normal_exit(char *msg, t_game *game)
// {
// 	free_array(game->real_map);
// 	free(game->map);
// 	free(game->player);
// 	free(game->img);
// 	mlx_terminate(game->mlx);
// 	ft_printf(msg);
// 	free(game);
// 	exit(EXIT_SUCCESS);
// }
