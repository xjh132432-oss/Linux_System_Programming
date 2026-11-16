#include <unistd.h>

int main()
{
    write(STDOUT_FILENO, "Normal output\n", 14);
    write(STDERR_FILENO, "Error message\n", 14);

    return 0;
}