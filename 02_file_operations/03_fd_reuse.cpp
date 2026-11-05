#include<unistd.h>
#include<fcntl.h>
#include<iostream>

int main()
{
    ssize_t fd1=open("day02_demo.txt",O_RDONLY);
    if(fd1==-1)
    {
        write(STDOUT_FILENO,
        "open failed",sizeof("open failed")-1);

        return 1;
    }
    ssize_t fd2=open("day02_demo.txt",O_RDONLY);
    if(fd2==-1)
    {
        write(STDOUT_FILENO,
        "open failed",sizeof("open failed")-1);

        return 1;
    }

    std::cout<<fd1<<'\n';
    std::cout<<fd2<<'\n';

    close(fd1);

    ssize_t fd3=open("day02_demo.txt",O_RDONLY);
    if(fd3==-1)
    {
        write(STDOUT_FILENO,
        "open failed",sizeof("open failed")-1);

        return 1;
    }

    std::cout<<fd3<<'\n';

    close(fd2);
    close(fd3);

    return 0;
}