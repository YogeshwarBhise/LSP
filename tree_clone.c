/*
Recursive Directory Traversal
Write tree_clone.c which prints a directory as a tree, like:

root/
    a.txt
    src/
        Ganesh.c

 Indentation based on recursion depth       

 Print type markers:
[D] directory
[F] Regular file
[L] Symbolic link

Use lstat() to detect symlinks
Do not follow symlink directories avoid loop

*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>

/* Function to print indentation based on depth */
void DisplayIndentation(int depth)
{
    int i = 0;
    for(i = 0; i < depth; i++)
    {
        printf("    ");   // 4 spaces per level
    }
}

/* Recursive directory traversal function */
void TraverseDirectory(const char *dirpath, int depth)
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

    while((ptr = readdir(dp)) != NULL)
    {
        /* Skip . and .. */
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        /* Build full path */
        snprintf(path, sizeof(path), "%s/%s", dirpath, ptr->d_name);

        /* Use lstat to avoid following symlinks */
        if(lstat(path, &sobj) == -1)
        {
            printf("%s\n", strerror(errno));
            continue;
        }

        DisplayIndentation(depth);

        /* Directory */
        if(S_ISDIR(sobj.st_mode))
        {
            printf("[D] %s/\n", ptr->d_name);
            TraverseDirectory(path, depth + 1);
        }
        /* Symbolic link */
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("[L] %s\n", ptr->d_name);
        }
        /* Regular file */
        else if(S_ISREG(sobj.st_mode))
        {
            printf("[F] %s\n", ptr->d_name);
        }
        /* Other types */
        else
        {
            printf("[?] %s\n", ptr->d_name);
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

    printf("[D] %s/\n", argv[1]);
    TraverseDirectory(argv[1], 1);

    return 0;
}