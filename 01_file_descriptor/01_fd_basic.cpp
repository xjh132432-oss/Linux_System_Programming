#include <iostream>
#include <unistd.h>

int main()
{
    std::cout << "stdin: " << STDIN_FILENO << '\n';
    std::cout << "stdout: " << STDOUT_FILENO << '\n';
    std::cout << "stderr: " << STDERR_FILENO << '\n';

    return 0;
}