#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>

int main()
{
    int fd=open("offset.txt",O_RDONLY);

    if(fd==-1)
    {
        write(STDOUT_FILENO,"open failed\n",12);
        return 1;
    }

    char buffer[128];
    //-----------first lseek--------------
    off_t pos=lseek(fd,10,SEEK_SET);

    if(pos==-1)
    {
        write(STDOUT_FILENO,"lseek failed",12);

        close(fd);
        return 1;
    }

    write(STDOUT_FILENO,"First position:",
        sizeof("First position:")-1);
    std::cout<<pos<<'\n';
    
    //-----------first read-----------
    ssize_t n=read(fd,buffer,5);

    if(n>0)

    {   
        std::cout<<"First data:";

        std::cout.write(buffer, n);

        std::cout<<'\n';


    }
    else if(n==0)
    {
        write(STDOUT_FILENO,"EOF",3);

        close(fd);
        return 1;
    }
    else{
        write(STDOUT_FILENO,"read failed",11);
        close(fd);

        return 1;
    }
    //-------------second lseek-------------
    off_t pos1=lseek(fd,3,SEEK_CUR);

    if(pos1==-1)
    {
        write(STDOUT_FILENO,"lseek failed",12);

        close(fd);
        return 1;
    }

    write(STDOUT_FILENO,"Second position:",
        sizeof("Second position:")-1);
    std::cout<<pos1<<'\n';
    //-----------second read------------------
    ssize_t n1=read(fd,buffer,4);

    if(n1>0)
    {   std::cout<<"Second data:";
        std::cout.write(buffer, n1);
        std::cout<<'\n';
    }
    else if(n1==0)
    {
        write(STDOUT_FILENO,"EOF",3);

        close(fd);
        return 1;
    }
    else{
        write(STDOUT_FILENO,"read failed",11);
        close(fd);

        return 1;
    }
    //-----------third lseek------------
    off_t pos2=lseek(fd,-5,SEEK_END);

    if(pos2==-1)
    {
        write(STDOUT_FILENO,"lseek failed",12);

        close(fd);
        return 1;
    }

    write(STDOUT_FILENO,"Third position:",
        sizeof("Third position:")-1);
    std::cout<<pos2<<'\n';
    
    //------------third read------------

    ssize_t n2=read(fd,buffer,5);

    if(n2>0)
    {   std::cout<<"Third data:";
        std::cout.write(buffer, n2);
        std::cout<<'\n';
    }
    else if(n2==0)
    {
        write(STDOUT_FILENO,"EOF",3);

        close(fd);
        return 1;
    }
    else{
        write(STDOUT_FILENO,"read failed",11);
        close(fd);

        return 1;
    }

    close(fd);

    return 0;
}