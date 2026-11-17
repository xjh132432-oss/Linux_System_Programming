#include<unistd.h>

int main()
{
    int pipfd[2];

    if(pipe(pipfd)==-1)
    {
        write(STDERR_FILENO,"pipe failed\n",12);

        return 1;
    }

    write(pipfd[1],"Hello Pipe",10);
    
    char buffer[10];

    read(pipfd[0],buffer,10);

    write(STDOUT_FILENO,buffer,10);

    close(pipfd[0]);
    close(pipfd[1]);

    return 0;
}