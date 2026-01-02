/*
Reverse File Content

Display the contents of the file in reverse Order

Input:
File Name

Output:
File Content printed in revers

*/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFFER_SIZE 100

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    char FileName[50];
    char TempFile[50] = "TempFile.txt";
    char Buffer[BUFFER_SIZE];
    int bytes_read = 0;
    int count = 0;  
    int Total = 0;
    

    printf("Enter the Filename : ");
    scanf("%s",FileName);

    fd1 = open(FileName,O_RDONLY);
    if(fd1 < 0)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    fd2 = open(TempFile,O_RDWR | O_CREAT | O_APPEND, 0777);
    if(fd2 < 0)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while((bytes_read = read(fd1,Buffer + Total,BUFFER_SIZE - Total)) > 0)
    {
        write(fd2,Buffer,bytes_read);
        Total = Total + bytes_read;
        count = count + bytes_read;
    }

    printf("Total bytes in the File are %s are : %d\n",FileName,count);
    

    for(int iCnt = count-1; iCnt>=0 ;iCnt--)
    {
        write(1,&Buffer[iCnt],1);
    }

   
    close(fd2);
    close(fd1);


    return 0;
}