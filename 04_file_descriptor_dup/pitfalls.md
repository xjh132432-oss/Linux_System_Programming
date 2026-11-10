# Day 04 Pitfalls

## 1. 未检查 open() 的返回值

问题：

open() 失败后返回 -1。如果继续执行 dup(fd1)，复制操作也会失败。

改进：

    int fd1 = open("offset.txt", O_RDONLY);

    if (fd1 == -1)
    {
        write(STDOUT_FILENO, "open failed\n", 12);
        return 1;
    }

## 2. 未检查 dup() 和 dup2() 的返回值

问题：

dup() 和 dup2() 失败时返回 -1。

如果不检查返回值，后续可能继续使用无效文件描述符。

改进：

    int fd2 = dup(fd1);

    if (fd2 == -1)
    {
        write(STDOUT_FILENO, "dup failed\n", 11);
        close(fd1);
        return 1;
    }

## 3. read() 返回值与 write() 长度不一致

问题：

read() 返回实际读取的字节数，不能假定每次读取都达到请求长度。

如果 write() 使用其他读取操作的返回值，可能导致输出长度错误。

例如：

    ssize_t n2 = read(fd2, buffer, 2);

正确输出：

    write(STDOUT_FILENO, buffer, n2);

## 4. 本日总结

本日主要需要注意：

- open()、dup()、dup2() 都需要检查返回值。
- read() 返回值决定实际读取的字节数。
- write() 应使用对应 read() 的实际返回值。
- 关闭文件描述符时，注意其他仍在使用的描述符。