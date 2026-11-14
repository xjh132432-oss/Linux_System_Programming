# Day 05 Pitfalls

## 1. 使用 O_CREAT 时缺少权限参数

问题：

使用 O_CREAT 打开文件时，没有提供第三个参数 mode。

错误示例：

    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC);

正确写法：

    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

原因：

当使用 O_CREAT 创建文件时，需要提供创建文件时请求的权限模式。

## 2. dup2() 检查了错误的变量

问题：

调用 dup2() 后，检查的仍然是原始文件描述符。

错误示例：

    dup2(fd, STDOUT_FILENO);

    if (fd == -1)
    {
        return 1;
    }

正确写法：

    int result = dup2(fd, STDOUT_FILENO);

    if (result == -1)
    {
        return 1;
    }

原因：

dup2() 的返回值才代表本次复制操作是否成功。

## 3. 重定向后错误信息也可能进入文件

问题：

执行：

    dup2(fd, STDOUT_FILENO);

之后，如果继续通过 STDOUT_FILENO 输出错误信息，错误信息也会进入目标文件。

改进：

    write(STDERR_FILENO, "dup2 failed\n", 12);

在只重定向 stdout 的情况下，stderr 仍然保持原来的输出目标。

## 4. 同时重定向时需要分别保存文件描述符

问题：

同时重定向 stdout 和 stderr 时，需要分别打开并保存两个文件描述符。

正确关系：

    fd1 → error.txt
    fd2 → output.txt

    dup2(fd2, STDOUT_FILENO);
    dup2(fd1, STDERR_FILENO);

不能覆盖其中一个文件描述符变量，否则可能丢失对已打开文件的引用。

## 5. 错误路径需要清理已打开的文件描述符

问题：

如果多个文件已经打开，其中一个操作失败，直接退出可能遗漏其他已打开文件描述符的显式关闭。

改进：

- 打开第二个文件失败时，关闭第一个文件。
- dup2() 失败时，关闭已经打开的原始文件描述符。
- 正常结束时关闭原始文件描述符。

注意：

关闭原始文件描述符不会关闭仍然被 FD 1 或 FD 2 引用的打开文件描述。

## 6. 本日总结

本日实际遇到并修正的问题：

- O_CREAT 缺少权限参数。
- dup2() 返回值检查错误。
- 错误信息输出目标选择不合理。
- 多文件描述符场景下的资源清理问题。