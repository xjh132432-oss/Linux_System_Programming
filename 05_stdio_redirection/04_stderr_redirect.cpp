#include<unistd.h>
#include<fcntl.h>
int main()
{
    int fd1=open("error.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
    
    if(fd1==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }

    int result=dup2(fd1,STDERR_FILENO);

    if(result==-1)
    {
        write(STDOUT_FILENO,"dup failed",10);
        close(fd1);
        return 1;
    }

    write(STDERR_FILENO,"Error occurred\n",15);

    write(STDOUT_FILENO,"Normal output\n",14);

    close(fd1);

    return 0;


}