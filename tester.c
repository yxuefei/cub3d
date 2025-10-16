/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:28:01 by omalovic          #+#    #+#             */
/*   Updated: 2025/10/16 14:57:24 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int	run_cub3d_on_file(const char *path, const char *filename, int file_count)
{
	char	buffer[4096];

	snprintf(buffer, sizeof(buffer) - 1, "./cub3d %s%s", path, filename);
	printf("\n----------FILE %d----------\n", file_count);
	printf("path: %s\n", buffer);
	if (system(buffer) == -1)
	{
		perror("system");
		return (-1);
	}
	return (0);
}

void	process_dir(const char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				file_count;

	file_count = 1;
	dir = opendir(path);
	if (!dir)
		return (perror("opendir"));
	printf("\n==========BAD MAPS==========\n");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		if (run_cub3d_on_file(path, entry->d_name, file_count) == -1)
			break ;
		file_count++;
		sleep(1);
		entry = readdir(dir);
	}
	closedir(dir);
}

int	main(void)
{
	char	*path_bad;

	path_bad = strdup("./maps/bad/");
	if (!path_bad)
		return (1);
	process_dir(path_bad);
	free(path_bad);
	return (0);
}

/* 
Caused problem (debug):

----------FILE 18----------
path: ./cub3d ./maps/bad/textures_dir.cub
MLX42: LodePNG: failed to open file for reading
Error: failed to load texture
*/