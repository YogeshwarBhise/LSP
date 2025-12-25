//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110

/*Move all files dir to dir 
Accept source and destination dir
Move all regular files
    use rename if same filesystem'
    else copy + delete
print count of moved files*/

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
    DIR *dp1 = NULL;
    DIR *dp2 = NULL;
    struct dirent *ptr1 = NULL;
    struct dirent *ptr2 = NULL;
    char DirSource[50];
    char DirDestination[50];
    struct stat sobj;
    char fullpath1[200];
    char fullpath2[200];
    char cwd1[200];
    char cwd2[200];
    int Counter = 0;

    printf("Enter the Directory source  : ");
    scanf("%s",DirSource);

    printf("Enter the Directory destination : ");
    scanf("%s",DirDestination);

    dp1 = opendir(DirSource);
    if(dp1 == NULL)
    {   printf("%s\n",strerror(errno));
        return -1;
    }

     dp2 = opendir(DirDestination);
    if(dp2 == NULL)
    {   printf("%s\n",strerror(errno));
        return -1;
    }

    /*while((ptr2 = readdir(dp2)) != NULL)
    {
        if(strcmp(ptr2->d_name,".") !=0 && strcmp(ptr2->d_name,"..") !=0)
        {
            snprintf(fullpath2, sizeof(fullpath2), "%s/%s", DirDestination, ptr2->d_name);
        }
    }*/
        while((ptr1 = readdir(dp1)) != NULL)
    {
        if(strcmp(ptr1->d_name,".") !=0 && strcmp(ptr1->d_name,"..") !=0)
        {
            snprintf(fullpath1, sizeof(fullpath1), "%s/%s", DirSource, ptr1->d_name);

             snprintf(fullpath2, sizeof(fullpath2), "%s/%s", DirDestination, ptr1->d_name); 
            ///stat(fullpath, &sobj);
           if(stat(fullpath1,&sobj) != 0)
                continue;
            
            if(S_ISREG(sobj.st_mode))
            {
                /*if(renameat(dp1,fullpath1,dp2,fullpath2)== 0)
                {
                    Counter++;
                }   */

                if(renameat(dirfd(dp1), ptr1->d_name,dirfd(dp2), ptr1->d_name) == 0)
                 {
                    Counter++;
                }   
            }

        }
    }

    printf("files moved %d\n",Counter);

    closedir(dp1);
    closedir(dp2);





    return 0;
}
//getcwd(cwd,sizeof(cwd));
/*
int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
    rename (      juna fd,    juna path,     navin fd,      navin path)



*/