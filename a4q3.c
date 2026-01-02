/*
File copy using pread and pwrite
Problem statement
Copy a file using pread and pwrite without changing the file offset

Input :
Source Filename and destination filename

Output
Copied file identical to source

*/


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<dirent.h>

#define Buffer_size 100

int main(int argc, char *argv[])
{
    int fd1 = 0;
    int fd2 = 0;
    off_t offsett = 0;
    char Buffer[Buffer_size];
    int bytes_read = 0;

    char Source[50];
    char Destination[50];

    printf("enter the  Source file is : \n");
    scanf("%s",Source);

    printf("enter the destination file is : \n");
    scanf("%s",Destination);

    //printf("enter the offset : \n");
    //scanf("%ld",&offsett);

    fd1 = open(Source,O_RDONLY);
    if(fd1 >= 0)
    {
        printf("Source File opened successfully\n");
    }
    else
    {
        printf("Source unable to open\n");
        printf("Reason : %s\n",strerror(errno));
    }

    fd2 = open(Destination,O_WRONLY | O_CREAT, 0777);
    if(fd2 >= 0)
    {
        printf("Destination File opened successfully\n");
    }
    else
    {
        printf("Destination unable to open\n");
        printf("Reason : %s\n",strerror(errno));
    }

    while((bytes_read = pread(fd1,Buffer,Buffer_size,offsett)) > 0)
    {
        pwrite(fd2,Buffer,bytes_read,offsett);
        offsett +=bytes_read;
    }


    close(fd1);
    close(fd1);

    return 0;
}


/*      ssize_t pread(size_t count; int fd, void buf[count], size_t count, off_t offset);
        ssize_t pwrite(size_t count; int fd, const void buf[count], size_t count, off_t offset); */