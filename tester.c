#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    const char *path_bad = "./maps/bad/";
    const char *path_good = "./maps/good/";
    DIR *dir_bad = opendir(path_bad);
    DIR *dir_good = opendir(path_good);

    if (!dir_bad || !path_good)
    {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    char buffer[4096];
    
    int file_count = 1;
    printf("==========BAD MAPS==========\n");
    while ((entry = readdir(dir_bad)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        printf("\n----------FILE %d----------\n", file_count);
        snprintf(buffer, sizeof(buffer) - 1, "./cub3d %s%s", path_bad, entry->d_name);
        printf("path: %s\n", buffer);
        int code = system(buffer);
        if (code == -1)
        {
            perror("system");
            break;
        }
        file_count++;
        sleep(1);
    }
    printf("\n\n==========GOOD MAPS==========\n");
    // while ((entry = readdir(dir_good)) != NULL)
    // {
    //     if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
    //         continue;
    //     printf("\n----------FILE %d----------\n", file_count);
    //     snprintf(buffer, sizeof(buffer) - 1, "./cub3d %s%s", path_bad, entry->d_name);
    //     printf("path: %s\n", buffer);
    //     int code = system(buffer);
    //     if (code == -1)
    //     {
    //         perror("system");
    //         break;
    //     }
    //     file_count++;
    //     sleep(1);
    // }
    closedir(dir_bad);
    closedir(dir_good);
}

/* 
Caused problem (debug):

----------FILE 18----------
path: ./cub3d ./maps/bad/textures_dir.cub
MLX42: LodePNG: failed to open file for reading
Error: failed to load texture
*/