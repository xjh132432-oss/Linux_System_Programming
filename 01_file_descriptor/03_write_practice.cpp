#include<unistd.h>
#include<iostream>

int main()
{
    char c1[]="linux",
        c2[]="System Programming"
        ,c3[]="File Descriptor";

    ssize_t v1=write(STDOUT_FILENO,c1,sizeof(c1)-1);
    write(1,"\n",1);
    ssize_t v2=write(STDOUT_FILENO,c2,sizeof(c2)-1);
    write(1,"\n",1);
    ssize_t v3=write(STDOUT_FILENO,c3,sizeof(c3)-1);
    write(1,"\n",1);

    std::cout<<"c1:"<<v1<<'\n';
    std::cout<<"c2:"<<v2<<'\n';
    std::cout<<"c3:"<<v3<<'\n';

    return 0;
}