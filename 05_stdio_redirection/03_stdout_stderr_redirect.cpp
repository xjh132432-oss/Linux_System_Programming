#include<unistd.h>
#include<fcntl.h>
int main()
{
    int fd2=open("output.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
    
    if(fd2==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }

    int result=dup2(fd2,STDOUT_FILENO);

    if(result==-1)
    {
        write(STDOUT_FILENO,"copy failed",11);
        close(fd2);
        return 1;
    }

    write(STDOUT_FILENO,"Message from stdout\n",20);

    write(STDERR_FILENO,"Message from stderr\n",20);

    close(fd2);

    return 0;


}