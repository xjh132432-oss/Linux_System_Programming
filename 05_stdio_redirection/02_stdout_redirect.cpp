#include<unistd.h>
#include<fcntl.h>
int main()
{
    int fd1=open("output.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
    
    if(fd1==-1)
    {
        write(STDOUT_FILENO,"open failed",11);
        return 1;
    }

    int result=dup2(fd1,STDOUT_FILENO);

    if(result==-1)
    {
        write(STDOUT_FILENO,"copy failed",11);
        close(fd1);
        return 1;
    }

    write(STDOUT_FILENO,"hello redirect\n",15);

    write(STDOUT_FILENO,"This goes into a file\n",22);

    close(fd1);

    return 0;


}