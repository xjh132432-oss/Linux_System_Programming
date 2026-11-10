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
    

    int fd2=dup2(fd1,10);

    std::cout<<fd1<<'\n';
    std::cout<<fd2<<'\n';

    char buffer[128];

    ssize_t n1=read(fd2,buffer,3);
    write(STDOUT_FILENO,"First:",7);
    write(STDOUT_FILENO,buffer,n1);
    write(STDOUT_FILENO,"\n",1);

    close(fd1);
    close(fd2);
    
    return 0;
}