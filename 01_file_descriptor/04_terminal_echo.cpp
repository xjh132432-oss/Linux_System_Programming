#include<unistd.h>

int main()
{
    char buffer[100];

    write(STDOUT_FILENO,"请输入内容:",16);

    ssize_t bytes_read=read(0,buffer,sizeof(buffer));

    if(bytes_read>0)
    {
        write(1,"你输入的内容是:",23);
        write(STDOUT_FILENO,buffer,bytes_read);
    }
    else if(bytes_read==0)
    {
        write(STDOUT_FILENO,"EOF",3);
    }
    else{
        write(STDOUT_FILENO,"ERROR\n",4);
    }

    return 0;
}