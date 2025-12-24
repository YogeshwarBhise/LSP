//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Read N byte from file
//Accept filename and Number for bytes N
//Read exactly N bytes using read and print on console
//if file contains less than N print only available bytes


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
    int N = 0;
    char Filename[50] = "";
    int fd = 0;
    int iRet = 0;
    char Buffer[SIZE_BUFFER];
    

    printf("Enter the File to open : \n");
    scanf("%s",Filename);

    printf("Enter the size of bytes you want to read : \n");
    scanf("%d",&N);

    fd = open(Filename,O_RDONLY);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("%s\n",strerror(errno));
        return -1;
    }

    iRet = read(fd,Buffer,N);

    //printf("Total bytes in file : %d\n",iRet);

    printf("Total number of bytes read %d\n",iRet);

    if(iRet > 0)
    {
        //write(fd,Buffer,iRet); //fd = 3
        write(1,Buffer,iRet); //fd = 1 stdout STDOUT_FILENO
    }
    close(fd);
    

    return 0;
}


//int stat(const char *restrict path, struct stat *restrict statbuf);
