#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=open("day02_demo.txt",O_RDONLY);

    if(fd==-1)
    {
        write(STDOUT_FILENO,
        "open failed",sizeof("open failed")-1);

        return 1;
    }
        
    char buffer[128];

    ssize_t bytes=read(fd,buffer,128);

    if(bytes<0) 
        write(STDOUT_FILENO,"READ ERROR",
        sizeof("READ ERROR"));


    if(bytes==0) write(STDOUT_FILENO,"EOF",3);

    if(bytes>0)
    write(STDOUT_FILENO,buffer,bytes);


    int close_code=close(fd);

    if(close_code==-1)
    write(STDOUT_FILENO,"close failed",12);

    return 0;

}