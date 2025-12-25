//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//check file present in directory
//Accept directory and  file
//check whether file exist in directory
//print absolue matched path if found

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUFFER_SIZE 100

int main()
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    char FileNAme[50];
    char DIRNAME[50];
    struct stat sobj;
    char fullpath[200];
    char cwd[200];

    printf("Enter the Filename : ");
    scanf("%s",FileNAme);

    printf("Enter the diretory : ");
    scanf("%s",DIRNAME);

    dp = opendir(DIRNAME);
    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }
    
   while((ptr = readdir(dp)) != NULL)
    {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", DIRNAME, ptr->d_name);
        
        stat(fullpath, &sobj);
        if(strcmp(ptr->d_name,FileNAme) == 0)
        {
            printf("File exists in directoiry %s/%s\n",DIRNAME,ptr->d_name);
            
            getcwd(cwd,sizeof(cwd));
            if(strcmp(DIRNAME,".") == 0)
            {
                snprintf(fullpath, sizeof(fullpath), "%s", ptr->d_name);
                printf("Full path %s/%s\n",cwd,fullpath);
            }
        }
    }
    closedir(dp);
    return 0;
}