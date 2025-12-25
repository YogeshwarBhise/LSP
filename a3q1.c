//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Copy file contents source to destination
//Accept sorce and destination file
//create destionation if not exust(O_CREAT O_TRUNC)
//copy using buffer read and write loop
//preserve permission using chnmod and stat

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
    char FileSource[50];
    char FileDestination[50];
    int fd1 = 0;
    int fd2 = 0;
    char Buffer[BUFFER_SIZE];
    int bytes_read = 0;
    int bytes_write = 0;
    struct stat sobj;

    printf("Enter the source Filename : ");
    scanf("%s",FileSource);

    fd1 = open(FileSource,O_RDONLY,0777);
    if(fd1 == -1)
    {
        printf("Source file unable to open\n");
        printf("Reason : %s\n",strerror(errno));
       return -1; 
    }
    else
    {
        printf("Source File exists\n");
    }

    printf("Enter the destination Filename : ");
    scanf("%s",FileDestination);

    fd2 = open(FileDestination,O_RDWR | O_CREAT | O_TRUNC,0777);

    if(fd2 == -1)
    {
        printf("destination file unable to open\n");
        printf("Reason : %s\n",strerror(errno));
        return -1;
    }
    else
    {
        printf("destination File exists\n");
        
    }

    if(stat(FileSource,&sobj) == 0)
    {
        chmod(FileDestination,sobj.st_mode);
    }
    
    while((bytes_read = read(fd1,Buffer,BUFFER_SIZE)) > 0)
    {
        bytes_write = write(fd2,Buffer,bytes_read);
    }

    

    close(fd1);
    close(fd2);

    return 0;
}