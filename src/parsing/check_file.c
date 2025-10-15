/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:51:04 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 17:47:29 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static bool	is_cub_file(char *arg)
{
	size_t	len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	if (len < 4)
		return (false);
	return (arg[len - 4] == '.' && arg[len - 3] == 'c'
		&& arg[len - 2] == 'u' && arg[len - 1] == 'b');
}

bool	is_png_file(char *arg)
{
	size_t	len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	if (len < 4)
		return (false);
	return (arg[len - 4] == '.' && arg[len - 3] == 'p'
		&& arg[len - 2] == 'n' && arg[len - 1] == 'g');
}

int	check_file(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error_general("Error: FILE_NOT_EXIST"), 0);
	close(fd);
	if (!is_cub_file(arg))
		return (error_general("Error: FILE_NOT_CUB"), 0);
	return (1);
}
