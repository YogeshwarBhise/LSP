//Name : Yogeshwar Pandurang Bhise
//RID : LSP01000110
//Display complete file information
//Accept filename and display file metadata using stat
//Size inode permission hardlink owner uid gid filetype last access modify
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include<time.h>

int main()
{
    struct stat sobj;
    char Filename[50] = "";


    printf("Enter the File to open : \n");
    scanf("%s",Filename);



    int iRet = stat(Filename,&sobj);

    if(iRet == -1)
    {
        printf("Error %s\n",strerror(errno));
        return -1;
    }

    printf("Inode number is : %ld\n",sobj.st_ino);
    printf("Hardlink count is : %ld\n",sobj.st_nlink);
    printf("Mode and permissions is : %o\n",sobj.st_mode);
    printf("UID number is : %u\n",sobj.st_uid);
    printf("GID number is : %u\n",sobj.st_gid);
    printf("Last Access time  is : %s\n",ctime(&sobj.st_atime));
    printf("Last Modify time  is : %s\n",ctime(&sobj.st_mtime));
    

    return 0;
}


//int stat(const char *restrict path, struct stat *restrict statbuf);
