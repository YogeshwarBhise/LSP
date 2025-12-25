//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//List all files from directory
//Accept directory name
//List opendir / readdir to print only names(skip . and ..)
//

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<sys/types.h>

#define SIZE_BUFFER 100

int main()
{
    int iRet = 0;
    char Directoryname[20];
    DIR *dp = NULL;
    struct dirent *ptr = NULL;


    printf("Enter the directory name : ");
    scanf("%s",Directoryname);


    dp = opendir(Directoryname);
    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
    }
   // while ((ptr = readdir(dp)) != NULL)

    while((ptr=readdir(dp)) != NULL)
    {
        if(strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name,"..")!= 0)
        {
            printf("opened File is %s\n",ptr->d_name);
        }
    }   
    closedir(dp);

    return 0;
}


//int stat(const char *restrict path, struct stat *restrict statbuf);



