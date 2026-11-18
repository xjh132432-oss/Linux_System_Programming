#include<unistd.h>
#include<iostream>
#include<stdio.h>

int main()
{
    char *args[]={
        (char *)"ls",
        (char *)"-l",
        nullptr
    };

    pid_t pid=fork();

    if(pid==-1)
    {
        std::cout<<"fork failed"<<'\n';
        return 1;
    }
    else if(pid==0)
    {
        execvp("ls",args);
        perror("execvp failed");
        _exit(127);
    }
    else{
        
        int status;

        waitpid(pid,&status,0);
        if(WIFEXITED(status))
        {
            std::cout<<"exit code:"<<WEXITSTATUS(status)<<'\n';
        }

        std::cout<<"child process finished\n";
    }


    return 0;
}