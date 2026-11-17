#include<unistd.h>
#include<iostream>

int main()
{
    pid_t pid=fork();

    if(pid==-1){
        write(STDERR_FILENO,"fork failes",11);
        return 1;
    }
    else if(pid==0)
    {
        std::cout<<"Childself pid:"<<getpid()<<'\n';
        std::cout<<"child ppid:"<<getppid()<<'\n';
    }
    else{
        std::cout<<"Parentself pid:"<<getpid()<<'\n';
        std::cout<<"child pid:"<<pid<<'\n';
    }

    return 0;
}