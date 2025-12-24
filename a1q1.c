//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Open file
//Accept filename from user and open it using open
//print success message and retuened file descriptot
//handle error using perror


#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    int fd = 0;

    fd = open("./Demo.txt",O_RDONLY);

    if(fd == -1)
    {
        printf("Unable to open the file\n%s\n",strerror(errno));
        
    }
    else
    {
        printf("File opened successfully , the File descriptor is : %d\n",fd);
    }

    return 0;
}

