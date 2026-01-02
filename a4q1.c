// Name : Yogeshwar Pandurang Bhise
//

/*
File copy utility
Problem statement
Write a program that writes the content of one file into another

Input :
Source Filename and destination filename as commandline arguments

Output
Destination file containing exact copy of the Source file
    -Handle file not found and permission error
    -Destination file should be created if not present

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
    char Buffer[Buffer_size];
    int bytes_read = 0;

    printf("the Source file is : %s\n",argv[1]);

    printf("the destination file is : %s\n",argv[2]);


    fd1 = open(argv[1],O_RDONLY);
    if(fd1 >= 0)
    {
        printf("Source File opened successfully\n");
    }
    else
    {
        printf("Source unable to open\n");
        printf("Reason : %s\n",strerror(errno));
    }

    fd2 = open(argv[2],O_WRONLY | O_CREAT, 0777);
    if(fd2 >= 0)
    {
        printf("Destination File opened successfully\n");
    }
    else
    {
        printf("Destination unable to open\n");
        printf("Reason : %s\n",strerror(errno));
    }

    while((bytes_read = read(fd1,Buffer,Buffer_size)) > 0)
    {
        write(fd2,Buffer,bytes_read);
    }


    close(fd1);
    close(fd1);

    return 0;
}