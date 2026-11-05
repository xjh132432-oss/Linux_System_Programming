#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=open("day02_demo.txt",
            O_WRONLY | O_CREAT | O_TRUNC,
            0644);

    if(fd>=0)
    {
        write(fd,"Linux System ProgrammingLearning open and close",
            sizeof("Linux System ProgrammingLearning open and close")-1);
    }
    if(fd<0){
        write(STDOUT_FILENO,"ERROR",5);
        return 1;
    }
    
    close(fd);

    return 0;

}