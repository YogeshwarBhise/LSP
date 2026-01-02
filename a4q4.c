/*
Merge File Utility
Merge multiple input files into single output file

Input:
Output_File Input_File Input_File Input_File ...

Output:
Combined File content in order

*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
//#include<>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
    char OutputFilename[50];
    int bytes_read = 0;
    int fdo = 0;
    int fdI = 0;
    int TotalInput = argc;
    int iCnt = 0;
    int Count = 2;
    char Buffer[BUFFER_SIZE];

    ///printf("Enter the Filename which you want as a Output File\n");
    ///scanf("%s",OutputFilename);

    fdo = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    if(fdo < 0)
    {
        printf("%s\n",strerror(errno));
    }
    else
    {
        printf("Output File created SuccessFully and the fd is %d\n",fdo);
    }

    for(iCnt = 0;iCnt<TotalInput-2;iCnt++)
    {
        fdI = open(argv[Count], O_RDONLY);
        if(fdI < 0)
            {
                printf("%s and Count %d\n",strerror(errno),Count);
            }
        
        write(fdo,argv[Count],strlen(argv[Count]));
        write(fdo,"\n",1);

        while((bytes_read = read(fdI,Buffer,BUFFER_SIZE)) > 0)
        {
            write(fdo,Buffer,bytes_read);
        }    

        write(fdo,"\n\n\n\n",4);

        Count = Count + 1;
        memset(Buffer,'\0',BUFFER_SIZE);
    }


    
    close(fdI);
    close(fdo);

    return 0;
}