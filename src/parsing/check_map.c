/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:31:54 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/15 18:46:32 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	validate_map(t_cub_data *d)
{
	int	h;

	if (!d || !d->map)
		return (0);
	h = get_map_height(d->map);
	if (h < 3)
		return (printf("Error: map too small\n"), 0);
	if (!check_borders(d->map, h))
		return (printf("Error: wrong border\n"), 0);
	if (!check_map_elements(d))
		return (0);
	if (!fix_and_validate_player_pos(d))
		return (printf("Error: invalid player position\n"), 0);
	if (!check_open_tiles_closed(d->map))
		return (printf("Error: map not closed\n"), 0);
	return (1);
}
