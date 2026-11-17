#include<unistd.h>
#include<iostream>
#include<sys/wait.h>

int main()
{
    pid_t pid1=fork();
    

    if(pid1==-1){
        write(STDERR_FILENO,"fork failes",11);
        return 1;
    }
    else if(pid1==0)
    {   
        std::cout<<"child1"<<'\n';
        std::cout<<"Child1 pid:"<<getpid()<<'\n';
        
    }
    else{
        pid_t pid2=fork();

        if(pid2==-1){
        write(STDERR_FILENO,"fork failes",11);
        return 1;
        }
        else if(pid2==0)
        {
            std::cout<<"child2"<<'\n';
            std::cout<<"Child2 pid:"<<getpid()<<'\n';
        }
        else{
            
            waitpid(pid1,nullptr,0);
            waitpid(pid2,nullptr,0);

            std::cout<<"All children finished"<<'\n';

        }
        
    }
    
    return 0;
}