//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Read whole file
//Accept filename and print whole content on console
//use buffer loop read until 0
//show total bytes read

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include<time.h>

#define SIZE_BUFFER 100

int main()
{
    char Buffer[SIZE_BUFFER];
    char Filename[20];
    int bytes_read = 0;
    int count = 0;
    int fd = 0;

    printf("Enter the file name : ");
    scanf("%s",Filename);

    fd = open(Filename,O_RDWR);


    while((bytes_read=read(fd,Buffer,SIZE_BUFFER))>0)
    {
        write(1,Buffer,bytes_read);
        count +=bytes_read;
    }
    printf("Total bytes read are %d \n: ",count);

    return 0;
}


//int stat(const char *restrict path, struct stat *restrict statbuf);



