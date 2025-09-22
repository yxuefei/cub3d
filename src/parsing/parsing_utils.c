/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:24:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/16 01:25:19 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	get_map_height(char **map)
{
	int	count;

	if (!map)
		return (0);
	count = 0;
	while (map[count])
		count++;
	return (count);
}