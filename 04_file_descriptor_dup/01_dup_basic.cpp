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

    std::cout<<fd1<<'\n';
    std::cout<<fd2<<'\n';

    close(fd1);
    close(fd2);
    
    return 0;
}