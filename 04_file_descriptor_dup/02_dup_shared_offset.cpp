#include<unistd.h>
#include<fcntl.h>
#include<iostream>

int main()
{
    int fd1=open("offset.txt",O_RDONLY);
    if(fd1==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }
    int fd2=dup(fd1);

    char buffer[128];

    ssize_t n1=read(fd1,buffer,3);
    write(STDOUT_FILENO,"First:",7);
    write(STDOUT_FILENO,buffer,n1);
    write(STDOUT_FILENO,"\n",1);
    
    write(STDOUT_FILENO,"Second:",8);
    ssize_t n2=read(fd2,buffer,3);
    write(STDOUT_FILENO,buffer,n2);

    close(fd1);
    close(fd2);
    
    return 0;
}