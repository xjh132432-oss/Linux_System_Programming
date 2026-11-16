#include <unistd.h>

int main()
{
    write(STDOUT_FILENO, "Hello Linux\n", 12);
    write(STDERR_FILENO, "Error Message\n", 14);

    return 0;
}