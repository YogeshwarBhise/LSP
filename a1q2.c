//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Accept filename and mode from user (R W RW A)
//Convert mode to flags O_RDONLY,O_WRONLY,O_RDWR, O_APPEND | O_CREAT
//open file accordingly and display fd
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char Filename[20] = "";
    char modeX[5] = "";
    char modeXX[20] = "";
    int Flagss = 0;
    

    printf("Enter the File to open : \n");
    scanf("%s",Filename);

    printf("Enter the mode to open the file: R - read, W - write, RW - read and write, A - append\n");
    scanf("%s",modeX);

    if(strcmp(modeX,"R") == 0)
    {
        Flagss = 1;
    }
    else if(strcmp(modeX,"W") == 0)
    {
        Flagss = 2;
    }
    else if(strcmp(modeX,"RW") == 0)
    {
        Flagss = 3;
    }
    else if(strcmp(modeX,"A") == 0)
    {
        Flagss = 4;
    } 

    switch(Flagss)
    {
        case 1:
            fd = open(Filename,O_RDONLY);
            strcpy(modeXX,"Read");
            break;
        case 2:
            fd = open(Filename,O_WRONLY);
            strcpy(modeXX,"Write");
            break;
        case 3:
            fd = open(Filename,O_RDWR);
            strcpy(modeXX,"Read and Write");
            break;
        case 4: 
            fd = open(Filename,O_RDWR | O_APPEND);
            strcpy(modeXX,"Append");
            break;
        default:
            printf("Enter correct value\n");
            break;
    }
    
    if(fd == -1)
    {
        printf("Unable to open the file\n%s\n",strerror(errno));
        
        return -1;
    }
    printf("File opened successfully , the File descriptor is : %d, and the mode is %s\n",fd,modeXX);
    
 


    return 0;
}