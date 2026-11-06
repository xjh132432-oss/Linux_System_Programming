#include<fcntl.h>
#include<unistd.h>
#include<iostream>

int main()
{
    int fd=open("offset.txt",O_RDONLY);

    char buffer[128];

    read(fd,buffer,2);
    write(STDOUT_FILENO,buffer,2);
    write(STDOUT_FILENO,"\n",1);

    read(fd,buffer,2);
    write(STDOUT_FILENO,buffer,2);
    write(STDOUT_FILENO,"\n",1);

    read(fd,buffer,2);
    write(STDOUT_FILENO,buffer,2);
    write(STDOUT_FILENO,"\n",1);
    
    close(fd);


    return 0;
}