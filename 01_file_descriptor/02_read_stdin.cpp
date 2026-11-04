#include<iostream>
#include<unistd.h>
#include<sys/types.h>

int main(){
    char buffer[5];

    std::cout<<"please enter:";
    std::cout.flush();

    ssize_t bytes_read=read(STDIN_FILENO,buffer,sizeof(buffer));

    if(bytes_read>0)
    {
        std::cout<<"读取字节"<<bytes_read<<'\n';
        std::cout<<"读取内容："<<'\n';
        std::cout.write(buffer,bytes_read);
    
    }
    else if(bytes_read==0)
    std::cout<<"没有读取到数据"<<'\n';
    else{
        std::cout<<"读取失败"<<'\n';
    }
    return 0;
}