#include<iostream>
#include<unistd.h>

int main()
{
    int sum=0;

    pid_t pid=fork();

    if(pid==-1)
    {
        std::cout<<"fork failed"<<'\n';
        return 1;
    }
    else if(pid==0)
    {
        sum=20;
        std::cout<<"Child sum:"<<sum<<'\n';
        std::cout<<"Child pid:"<<getpid()<<'\n';
    }
    else{
        sum=30;
        std::cout<<"Parent sum:"<<sum<<'\n';
        std::cout<<"Parent pid:"<<getpid()<<'\n';
    }


    return 0;
}