#include<unistd.h>
#include<fcntl.h>
#include<iostream>

int main()
{   
    int fd = open("flag_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        std::cout << "open failed\n";
        return 1;
    }

    ssize_t wn = write(fd, "First line", sizeof("First line") - 1);
    if(wn == -1)
    {
        std::cout << "write failed\n";
        close(fd);
        return 1;
    }

    close(fd);


    int fd1 = open("flag_test.txt", O_WRONLY | O_APPEND);
    if(fd1 < 0)
    {
        std::cout << "open failed\n";
        return 1;
    }

    wn = write(fd1, "Second line", sizeof("Second line") - 1);
    if(wn == -1)
    {
        std::cout << "write failed\n";
        close(fd1);
        return 1;
    }

    close(fd1);


    int fd2 = open("flag_test.txt", O_RDONLY);
    if(fd2 < 0)
    {
        std::cout << "open failed\n";
        return 1;
    }

    char buffer[128];
    ssize_t n = read(fd2, buffer, sizeof(buffer));
    if(n > 0)
    {
        ssize_t outn = write(STDOUT_FILENO, buffer, n);
        if(outn == -1)
        {
            std::cout << "stdout write failed\n";
            close(fd2);
            return 1;
        }
    }
    else if(n == 0)
    {
        std::cout << "EOF\n";
    }
    else
    {
        std::cout << "read failed\n";
        close(fd2);
        return 1;
    }

    close(fd2);
    
    return 0;
}
