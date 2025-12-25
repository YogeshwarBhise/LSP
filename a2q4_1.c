//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//List all files with type
//Print each entry with its type : regualr directory link fifo socket char block
//use lstat for accurate type

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



            iRet = lstat(Path,&sobj);
            if(iRet == 0)
            {
                printf("Successfully got the metadata\n");   
            }
            else
            {
                printf("Unable to retrive the metadata\n");
                printf("%s\n",strerror(errno));
            }

        switch(sobj.st_mode & S_IFMT)
        {
            //regualr directory link fifo socket char block
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
        }
            

        }

        printf("================================\n");
    }   
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