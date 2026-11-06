#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int fd=open("offset.txt",O_RDONLY);

    if(fd==-1)
    {
        write(STDOUT_FILENO,"open failed",12);

        return 1;
    }
    off_t pos=lseek(fd,-4,SEEK_END);

    if(pos==-1)
    {
        write(STDOUT_FILENO,"lseek failed",12);

        close(fd);
        return 1;
    }

    char buffer[128];

    ssize_t n=read(fd,buffer,4);

    if(n>0)
    {
        write(STDOUT_FILENO,buffer,n);
    }
    else if(n==0)
    {
        write(STDOUT_FILENO,"EOF",3);

        close(fd);
        return 1;
    }
    else{
        write(STDOUT_FILENO,"read failed",11);
        close(fd);

        return 1;
    }

    close(fd);

    return 0;
}