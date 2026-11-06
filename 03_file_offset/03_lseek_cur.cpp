#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd=open("offset.txt",O_RDONLY);

    if(fd==-1)
    {
        write(STDOUT_FILENO,"open faailed",12);

        return 1;
    }

    char buffer[128];

    ssize_t n1=read(fd,buffer,3);

    if(n1>0)
    write(STDOUT_FILENO,buffer,n1);
    else if(n1==0)
    write(STDOUT_FILENO,"EOF",3);
    else{
        write(STDOUT_FILENO,"READ FAILED",12);
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO,"\n",1);

    off_t pos=lseek(fd,2,SEEK_CUR);

    if(pos==-1)
    {
        write(STDOUT_FILENO,"lseek failed",12);
        close(fd);

        return 1;
    }

    ssize_t n=read(fd,buffer,3);

    if(n>0)
    write(STDOUT_FILENO,buffer,n);
    else if(n==0)
    write(STDOUT_FILENO,"EOF",3);
    else{
        write(STDOUT_FILENO,"READ FAILED",12);
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}