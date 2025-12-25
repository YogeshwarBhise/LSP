//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Find largest File in directory
//Accpet directory name
//find and print:
//  largest filename
//  its size in bytes
//Consider only regular files ignore directory


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
    struct stat sobj;
    char Path[100];
    off_t max = 0;
    char maxName[20];

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
            memset(Path, '\0', sizeof(Path));
            getcwd(Path,sizeof(Path));
            strcat(Path, "/");
            strcat(Path, Directoryname);
            strcat(Path, "/");
            strcat(Path, ptr->d_name);

           // snprintf(Path, sizeof(Path), "%s/%s", Directoryname, ptr->d_name);


            iRet = lstat(Path,&sobj);
            if(iRet == 0)
            {
               // printf("Successfully got the metadata\n");   
            }
            else
            {
                printf("Unable to retrive the metadata\n");
                printf("%s\n",strerror(errno));
            }

            if (lstat(Path, &sobj) == -1)
            {
                continue;
            }



            switch(sobj.st_mode & S_IFMT)
            {
                case S_IFREG:
                        if(sobj.st_size > max)
                        {
                            max = sobj.st_size;
                            strcpy(maxName,ptr->d_name);
                        }
                        break;
                default:
                    break;
            }

        }
    
        printf("================================\n");
    }   
    printf("Max size of file is %ld\n",max);
    printf("File name of biggest file is %s\n",maxName);
    closedir(dp);

    return 0;
}



/*

struct stat {
           dev_t      st_dev;      /* ID of device containing file 
           ino_t      st_ino;      /* Inode number 
           mode_t     st_mode;     /* File type and mode 
           nlink_t    st_nlink;    /* Number of hard links 
           uid_t      st_uid;      /* User ID of owner 
           gid_t      st_gid;      /* Group ID of owner 
           dev_t      st_rdev;     /* Device ID (if special file) 
           off_t      st_size;     /* Total size, in bytes 
           blksize_t  st_blksize;  /* Block size for filesystem I/O 
           blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated 

*/           