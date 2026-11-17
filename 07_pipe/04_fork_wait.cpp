#include<iostream>
#include<sys/wait.h>
#include<unistd.h>

int main()
{

    pid_t pid=fork();

    if(pid==-1)
    {
        std::cout<<"fork failed"<<'\n';
    }
    else if(pid==0)
    {
        std::cout<<"Child is running"<<'\n';
        sleep(2);
        std::cout<<"chid finished"<<'\n';
    }
    else{
        waitpid(pid,nullptr,0);
        std::cout<<"Parent finished waiting"<<'\n';
    }


    return 0;
}