/*
Directory Traversal Basics

Create a program ls_clone.c that takes one directory path and prints:

Entry name
Type(file/dir/link/other)
Size(bytes)
Permissions in rwxr-xr-x format
Last modified time
Skip . and ..
Build Full path using snprintf(dir + "/" + name).

*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include<time.h>


const char *FileType(mode_t mode)
{
    if (S_ISREG(mode))  
        return "file";
    if (S_ISDIR(mode))  
        return "dir";
    if (S_ISLNK(mode))  
        return "link";
    return "other";
}


void DisplayPermissions(mode_t mode)
{
    char permission[11];

    permission[0] = (S_ISDIR(mode)) ? 'd' :
              (S_ISLNK(mode)) ? 'l' : '-';

    permission[1] = (mode & S_IRUSR) ? 'r' : '-';
    permission[2] = (mode & S_IWUSR) ? 'w' : '-';
    permission[3] = (mode & S_IXUSR) ? 'x' : '-';

    permission[4] = (mode & S_IRGRP) ? 'r' : '-';
    permission[5] = (mode & S_IWGRP) ? 'w' : '-';
    permission[6] = (mode & S_IXGRP) ? 'x' : '-';

    permission[7] = (mode & S_IROTH) ? 'r' : '-';
    permission[8] = (mode & S_IWOTH) ? 'w' : '-';
    permission[9] = (mode & S_IXOTH) ? 'x' : '-';

    permission[10] = '\0';

    printf("permission are : %s\n", permission);

}

int main(int argc, char *argv[])
{
    DIR *dp = NULL;   //Points to the directory stream
    struct dirent *ptr = NULL; //Holds one directory entry at a time
    struct stat sobj;
    char path[1024];          

    if(argc != 2)
    {
        printf("Enter the second argument as Directory that needs to be traversed\n");
        return -1;
    }

    dp = opendir(argv[1]);
    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp)) != NULL)
    {
        if((strcmp(ptr->d_name,".")) == 0 || (strcmp(ptr->d_name,"..")) == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s",argv[1],ptr->d_name);    
    
        //if((stat(path,&sobj)) == -1)// issue for symlink
        if((lstat(path,&sobj)) == -1)
        {
            printf("%s\n",strerror(errno));
        }
    
        printf("Name is : %s\n",ptr->d_name);
        printf("Type is : %s\n",FileType(sobj.st_mode));
        printf("Size of bytes occupied is : %ld\n",sobj.st_size);
        
        DisplayPermissions(sobj.st_mode);

        printf("Modified date is : %s\n",ctime(&sobj.st_mtime));

    }
    closedir(dp);

    return 0;
}