#include<unistd.h>
#include<sys/wait.h>
#include<iostream>

int main()
{
    

    int pipefd[2];

    if(pipe(pipefd)==-1)
    {
        std::cout<<"pipe failed"<<'\n';
        return 1;
    }

    pid_t pid=fork();

    if(pid==-1)
    {
        std::cout<<"fork failed\n";
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }
    else if(pid==0)
    {
        close(pipefd[0]);
        write(pipefd[1],"hello from child",16);
        close(pipefd[1]);

    }
    else{
        
        close(pipefd[1]);
        char buffer[17];

        read(pipefd[0],buffer,16);

        std::cout<<"Parent received:";
        std::cout<<buffer<<'\n';
        std::cout<<"Bytes read:"<<sizeof(buffer);

        waitpid(pid,nullptr,0);

        close(pipefd[0]);

    }

    return 0;
}