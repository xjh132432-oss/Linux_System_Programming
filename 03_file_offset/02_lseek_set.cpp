#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
    int fd=open("offset.txt",O_RDONLY);

    if(fd==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        write(STDOUT_FILENO,"\n",1);

        return 1;
    }

    off_t pos=lseek(fd,5,SEEK_SET);

    if(pos==-1)
    {
        write(STDOUT_FILENO,
            "lseek failed\n",13);
        close(fd);

        return 1;
    }

    char buffer[128];

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