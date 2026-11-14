#include<unistd.h>
#include<fcntl.h>
int main()
{
    int fd1=open("error.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
    int fd2=open("output.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
    
    if(fd1==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }
    if(fd2==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        close(fd1);
        return 1;
    }

    int result1=dup2(fd2,STDOUT_FILENO);

    if(result1==-1)
    {
        write(STDOUT_FILENO,"copy failed",11);
        close(fd2);
        return 1;
    }

    int result2=dup2(fd1,STDERR_FILENO);

    if(result2==-1)
    {
        write(STDOUT_FILENO,"dup failed",10);
        close(fd1);
        close(fd2);
        return 1;
    }

    write(STDERR_FILENO,"Error message 1\n",16);
    write(STDERR_FILENO,"Error message 2\n",16);

    write(STDOUT_FILENO,"Normal output 1\n",16);
    write(STDOUT_FILENO,"Normal output 2\n",16);

    close(fd1);
    close(fd2);
    return 0;


}