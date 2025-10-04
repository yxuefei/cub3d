/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 10:53:01 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 10:53:21 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	row_len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	first_noblank_idx(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] && is_blank((unsigned char)s[i]))
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

int	last_noblank_idx(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = row_len(s) - 1;
	while (i >= 0 && is_blank((unsigned char)s[i]))
		i--;
	return (i);
}
