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
    if(fd2==-1){
        write(STDOUT_FILENO,"dup failed",11);
        return 1;
    }

    int fd3=open("offset.txt",O_RDONLY);
    if(fd3==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }

    char buffer[128];

    ssize_t n1=read(fd1,buffer,2);
    if(n1<0)
    {
        write(STDOUT_FILENO,"read failed",12);
        return 1;
    }
    if(n1==0)
    {
        write(STDOUT_FILENO,"EOF",4);
    }
    else{
        write(STDOUT_FILENO,"fd1:",4);
        write(STDOUT_FILENO,buffer,n1);
        write(STDOUT_FILENO,"\n",1);
    }
    
    
    ssize_t n2=read(fd2,buffer,2);
    if(n2<0)
    {
        write(STDOUT_FILENO,"read failed",12);
        return 1;
    }
    if(n2==0)
    {
        write(STDOUT_FILENO,"EOF",4);
    }
    else{
        write(STDOUT_FILENO,"fd2:",4);
        write(STDOUT_FILENO,buffer,n2);
        write(STDOUT_FILENO,"\n",1);
    }

    ssize_t n3=read(fd3,buffer,2);
    if(n3<0)
    {
        write(STDOUT_FILENO,"read failed",12);
        return 1;
    }
    if(n3==0)
    {
        write(STDOUT_FILENO,"EOF",4);
    }
    else{
        write(STDOUT_FILENO,"fd3:",4);
        write(STDOUT_FILENO,buffer,n3);
        write(STDOUT_FILENO,"\n",1);
    }

    close(fd1);
    ssize_t n4=read(fd2,buffer,2);
    if(n4<0)
    {
        write(STDOUT_FILENO,"read failed",12);
        return 1;
    }
    if(n4==0)
    {
        write(STDOUT_FILENO,"EOF",4);
    }
    else{
        write(STDOUT_FILENO,"fd2 after close fd1:",21);
        write(STDOUT_FILENO,buffer,n4);
        write(STDOUT_FILENO,"\n",1);
    }

    close(fd3);
    close(fd2);
    
    return 0;
}