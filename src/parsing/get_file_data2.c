/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:18:59 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/04 11:22:48 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	skip_ws(const char *s, int *i)
{
	while (s[*i] && is_blank((unsigned char)s[*i]))
		(*i)++;
}

int	starts_with_id(const char *s, const char *id)
{
	int	i;
	int	k;

	i = 0;
	skip_ws(s, &i);
	k = 0;
	while (id[k])
	{
		if (s[i + k] != id[k])
			return (0);
		k++;
	}
	return (1);
}

int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	skip_ws(s, &i);
	return (s[i] == '0' || s[i] == '1');
}

int	is_nonblank_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_blank((unsigned char)s[i]) && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
