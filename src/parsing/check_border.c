/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:02:24 by xueyang           #+#    #+#             */
/*   Updated: 2025/10/01 16:22:42 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

// static int	effective_end(const char *s)
// {
// 	int	i;

// 	if (!s)
// 		return (-1);
// 	i = 0;
// 	while (s[i] && s[i] != '\n')
// 		i++;
// 	return (i - 1);
// }

// int	check_top(char **map)
// {
// 	int		j;
// 	char	*row;

// 	if (!map || !map[0])
// 		return (1);
// 	row = map[0];
// 	j = 0;
// 	while (row[j] && row[j] != '\n' && is_blank(row[j]))
// 		j++;
// 	if (!row[j] || row[j] == '\n')
// 		return (1);
// 	//problem is here, here returns 1 too early
// 	while (row[j] && row[j] != '\n')
// 	{
// 		if (row[j] != '1')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// int	check_bottom(char **map, int map_height)
// {
// 	int		j;
// 	char	*row;

// 	if (!map || map_height <= 0 || !map[map_height - 1])
// 		return (1);
// 	row = map[map_height - 1];
// 	j = 0;
// 	while (row[j] && row[j] != '\n' && is_blank(row[j]))
// 		j++;
// 	if (!row[j] || row[j] == '\n')
// 		return (1);
// 	while (row[j] && row[j] != '\n')
// 	{
// 		if (row[j] != '1')
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// int	check_left(char **map, int map_height)
// {
// 	int		i;
// 	int		j;
// 	char	*row;

// 	if (!map || map_height < 3)
// 		return (1);
// 	i = 1;
// 	while (i < map_height - 1)
// 	{
// 		row = map[i];
// 		if (!row)
// 			return (1);
// 		j = 0;
// 		while (row[j] && row[j] != '\n' && is_blank(row[j]))
// 			j++;
// 		if (!row[j] || row[j] == '\n' || row[j] != '1')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	check_right(char **map, int map_height)
// {
// 	int		i;
// 	int		end;
// 	char	*row;

// 	if (!map || map_height < 3)
// 		return (1);
// 	i = 1;
// 	while (i < map_height - 1)
// 	{
// 		row = map[i];
// 		if (!row)
// 			return (1);
// 		end = effective_end(row);
// 		if (end < 0)
// 			return (1);
// 		while (end >= 0 && is_blank(row[end]))
// 			end--;
// 		if (end < 0 || row[end] != '1')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	check_borders(char **map, int map_height)
// {
// 	if (check_top(map))
// 		return (0);
// 	printf("haha1\n");
// 	if (check_bottom(map, map_height))
// 		return (0);
// 	printf("haha2\n");
// 	if (check_left(map, map_height))
// 		return (0);
// 	printf("haha3\n");
// 	if (check_right(map, map_height))
// 		return (0);
// 	printf("haha4\n");
// 	return (1);
// }

/* ========= 小工具 ========= */

static int	is_blank_char(int c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

/* 行内有效长度（不含 '\0'；你已去掉 '\n'，这里不需要处理 '\n'） */
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

/* 找到行内第一个非空白字符位置；若整行空白返回 -1 */
static int	first_noblank_idx(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] && is_blank_char((unsigned char)s[i]))
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

/* 找到行内最后一个非空白字符位置；若整行空白返回 -1 */
static int	last_noblank_idx(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = row_len(s) - 1;
	while (i >= 0 && is_blank_char((unsigned char)s[i]))
		i--;
	return (i);
}

/* ========= 顶/底边界 ========= */

/* 顶行：所有非空白必须是 '1' */
int	check_top_border(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = first_noblank_idx(map[0]);
	if (i < 0)
		return (0);
	while (map[0][i])
	{
		if (!is_blank_char((unsigned char)map[0][i])
			&& map[0][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

/* 底行：所有非空白必须是 '1' */
int	check_bottom_border(char **map, int h)
{
	int	i;

	if (!map || h <= 0 || !map[h - 1])
		return (0);
	i = first_noblank_idx(map[h - 1]);
	if (i < 0)
		return (0);
	while (map[h - 1][i])
	{
		if (!is_blank_char((unsigned char)map[h - 1][i])
			&& map[h - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

/* ========= 左/右边界 ========= */

/* 左边界：每一行的“第一个非空白”必须是 '1' */
int	check_left_border(char **map, int h)
{
	int	y;
	int	x;

	if (!map || h <= 0)
		return (0);
	y = 0;
	while (y < h)
	{
		x = first_noblank_idx(map[y]);
		if (x < 0)
			return (0);
		if (map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

/* 右边界：每一行的“最后一个非空白”必须是 '1' */
int	check_right_border(char **map, int h)
{
	int	y;
	int	x;

	if (!map || h <= 0)
		return (0);
	y = 0;
	while (y < h)
	{
		x = last_noblank_idx(map[y]);
		if (x < 0)
			return (0);
		if (map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

/* ========= 汇总 ========= */
/* 注意：返回 1=通过，0=失败（和 validate_map 配合好） */
int	check_borders(char **map, int h)
{
	if (!check_top_border(map))
		return (0);
	if (!check_bottom_border(map, h))
		return (0);
	if (!check_left_border(map, h))
		return (0);
	if (!check_right_border(map, h))
		return (0);
	return (1);
}
