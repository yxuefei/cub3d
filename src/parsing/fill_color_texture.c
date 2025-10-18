/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:09:03 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/18 15:41:54 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	set_floor_color_from_line(t_cub_data *d, const char *line)
{
	int	i;
	int	color;

	if (!d || !line)
		return (0);
	i = 0;
	skip_ws(line, &i);
	if (line[i] == 'F')
	{
		i++;
		skip_ws(line, &i);
	}
	color = parse_color_string(line + i);
	if (color == -1)
		return (0);
	d->floor_color = color;
	return (1);
}

int	set_ceiling_color_from_line(t_cub_data *d, const char *line)
{
	int	i;
	int	color;

	if (!d || !line)
		return (0);
	i = 0;
	skip_ws(line, &i);
	if (line[i] == 'C')
	{
		i++;
		skip_ws(line, &i);
	}
	color = parse_color_string(line + i);
	if (color == -1)
		return (0);
	d->ceiling_color = color;
	return (1);
}
