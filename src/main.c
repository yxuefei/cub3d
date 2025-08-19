/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:24:30 by xueyang           #+#    #+#             */
/*   Updated: 2025/08/19 16:21:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	check_file_name(char **av)
{
	int	i;

	i = ft_strlen(av[1]);
	if (i < 5 || av[1][i - 1] != 'r' || av[1][i - 2] != 'e' || \
		av[1][i - 3] != 'b' || av[1][i - 4] != '.')
		error_general("argument error: map file name must end with .ber");
}

// int	main(int ac, char **av)
// {
// 	t_game	*game;

// 	if (ac != 2)
// 		error_general("argument error: arg num wrong");
// 	check_file_name(av);
// 	game = init_game(av);
// 	place_img(game, game->real_map);
// 	mlx_key_hook(game->mlx, key_hook, game);
// 	mlx_loop(game->mlx);
// 	mlx_terminate(game->mlx);
// 	return (EXIT_SUCCESS);
// }



// void	checkleak(void)
// {
// 	system("leaks so_long");
// }
// atexit(&checkleak);
