//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Accept filename and mode from user (R W execute)
//use access() to check permissions
//print access or not with reason
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include <sys/syscall.h>

int main()
{
    int fd = 0;
    char Filename[20] = "";
    char modeX = '\0';
    int Flagss = 0;
    
    

    printf("Enter the File to open : \n");
    scanf("%s",Filename);

    if(access(Filename,F_OK) != 0)
    {
        printf("File does not exist\n");
        return -1;
    }

    printf("Enter the mode to check access : R - read, W - write, E - Execute\n");
    scanf(" %c",&modeX);
   
    if(modeX == 'R')
    {
        Flagss = 1;
    }
    else if(modeX == 'W')
    {
        Flagss = 2;
    }
    else if(modeX == 'E')
    {
        Flagss = 3;
    }

    switch(Flagss)
    {
        case 1:
            //printf("Readable\n");
            if(access(Filename,R_OK) == 0)
            {
                printf("Readable\n");
            }
            else
            {
                printf("%s\n",strerror(errno));
            }
            break;
        case 2:
            if(access(Filename,W_OK) == 0)
            {
                printf("Writable\n");
            }
            else
            {
                printf("%s\n",strerror(errno));
            }
            break;
        case 3:
            if(access(Filename,X_OK) == 0)
            {
                printf("Executable\n");
            }
            else
            {
                printf("%s\n",strerror(errno));
            }
            break;    
    }


    return 0;
}