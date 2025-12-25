//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Write string to file
//Accept filename and String from user
//write string using write(Appens mode by default)
//show total bytes written

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
    char StringX[20];
    int bytes_read = 0;
    int count = 0;
    int fd = 0;

    printf("Enter the file name : ");
    scanf("%s",Filename);

    printf("Enter the Strng to write  : ");
    scanf("%s",StringX);

    fd = open(Filename,O_RDWR | O_CREAT | O_APPEND, 0777);

    if(fd > 0)
    {
        printf("Successfully file opened \n");
    }
    else
    {
        printf("Unable to open the file\n");
        printf("Reason : %s\n",strerror(errno));
        return -1;
    }

    int iCnt = 0;
   while(StringX[iCnt] != '\0' )
   {
        count = count+1; 
        iCnt++;
   }

   printf("Size of string is %d\n",count);

   int iRet = write(fd,StringX,count);

   if(iRet > 0)
   {
    printf("Total bytes written are %d\n",iRet);
   }
   else
   {
    printf("Unable to write \n");
    printf("%s\n",strerror(errno));
   }

   close(fd);


    return 0;
}


//int stat(const char *restrict path, struct stat *restrict statbuf);



