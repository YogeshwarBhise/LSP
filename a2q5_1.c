#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main()
{
    char Directoryname[256];
    DIR *dp;
    struct dirent *ptr;
    struct stat sobj;
    char Path[512];
    off_t max = 0;
    char maxName[256] = "";

    printf("Enter the directory name: ");
    scanf("%255s", Directoryname);

    dp = opendir(Directoryname);
    if (!dp)
    {
        perror("opendir");
        return 1;
    }

    while ((ptr = readdir(dp)) != NULL)
    {
        if (!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, ".."))
            continue;

        snprintf(Path, sizeof(Path), "%s/%s", Directoryname, ptr->d_name);

        if (lstat(Path, &sobj) == -1)
            continue;

        if (S_ISREG(sobj.st_mode))
        {
            if (sobj.st_size > max)
            {
                max = sobj.st_size;
                strcpy(maxName, ptr->d_name);
            }
        }
    }

    closedir(dp);

    if (maxName[0] == '\0')
        printf("No regular files found\n");
    else
    {
        printf("Max size of file is %ld bytes\n", max);
        printf("File name of biggest file is %s\n", maxName);
    }

    return 0;
}
