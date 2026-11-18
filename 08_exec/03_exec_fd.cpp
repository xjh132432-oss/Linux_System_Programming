#include<unistd.h>
#include<iostream>
#include<stdio.h>
#include<fcntl.h>

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
    {   int fd=open("output.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);

        if(fd==-1)
        {
            std::cout<<"open failed\n";
            return 1;
        }
        
        dup2(fd,STDOUT_FILENO);
        close(fd);

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