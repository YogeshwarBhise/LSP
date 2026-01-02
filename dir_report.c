/*
File Counter + Size Report
Create dir_report.c that recursivley calculates:

total number of files
Total number of directories
Total size of regular Files(inbytes)
Largest filename + size
Count a directory when you enter it
for size:consider only regular files(S_ISREG)
Ignore symlink target size(treat symlink as link object only)

Output:
Example : 

    Files : 120
    Dirs : 15
    Total size: 9823412 bytes
    Largest : Marvellous.mp4

*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>


long TotalFiles = 0;
long TotalDirs = 0;
long TotalSize = 0;

long LargestSize = 0;
char LargestFile[1024];


void DirectoryReport(const char *dirpath)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char path[1024];

    dp = opendir(dirpath);
    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
        return;
    }

    
    TotalDirs++;

    while((ptr = readdir(dp)) != NULL)
    {
        
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        
        snprintf(path, sizeof(path), "%s/%s", dirpath, ptr->d_name);

        
        if(lstat(path, &sobj) == -1)
        {
            printf("%s\n", strerror(errno));
            continue;
        }

        if(S_ISDIR(sobj.st_mode))
        {
            DirectoryReport(path);
        }
        
        else if(S_ISREG(sobj.st_mode))
        {
            TotalFiles++;
            TotalSize = TotalSize + sobj.st_size;

            
            if(sobj.st_size > LargestSize)
            {
                LargestSize = sobj.st_size;
                strcpy(LargestFile, ptr->d_name);
            }
        }
        
        else if(S_ISLNK(sobj.st_mode))
        {
           
            continue;
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Enter directory name as argument\n");
        return -1;
    }

    DirectoryReport(argv[1]);

    printf("\nFiles : %ld\n", TotalFiles);
    printf("Dirs : %ld\n", TotalDirs);
    printf("Total size : %ld bytes\n", TotalSize);
    printf("Largest : %s (%ld bytes)\n", LargestFile, LargestSize);

    return 0;
}
