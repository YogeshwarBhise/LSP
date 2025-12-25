////Name : Yogeshwar Pandurang Bhise
////RID : LSP01000110
/*Delete all empty regular files Accept the directory name delete file with size 0 only regular file printname deleted + total deleted count */


#include<stdio.h>      // printf, scanf
#include<string.h>     // strcmp
#include<unistd.h>     // unlink
#include<dirent.h>     // DIR, readdir
#include<sys/stat.h>   // stat, S_ISREG
#include<errno.h>      // perror

int main()
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    char DirName[50];
    char FullPath[200];
    struct stat sobj;
    int Count = 0;

    printf("Enter Directory Name : ");
    scanf("%s", DirName);

    dp = opendir(DirName);
    if(dp == NULL)
    {
        perror("opendir");
        return -1;
    }

    while((ptr = readdir(dp)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(FullPath, sizeof(FullPath),"%s/%s", DirName, ptr->d_name);
    
        if(stat(FullPath, &sobj) != 0)
        {
            continue;
        }

        if(S_ISREG(sobj.st_mode) && sobj.st_size == 0)
        {
            if(unlink(FullPath) == 0)
            {
                printf("Deleted file : %s\n", ptr->d_name);
                Count++;
            }
        }
    }
    closedir(dp);    
    printf("Total files deleted : %d\n", Count);

    return 0;
}