# Day 05：标准输入、标准输出与文件描述符重定向

## 1. 学习目标

理解 Linux 进程的三个标准文件描述符，掌握使用 dup2() 实现标准输出和标准错误重定向。

本日重点：

- 理解 stdin、stdout、stderr。
- 理解标准文件描述符 0、1、2。
- 使用 open() 打开重定向目标文件。
- 使用 dup2() 修改标准输出的指向。
- 使用 dup2() 修改标准错误的指向。
- 同时重定向 stdout 和 stderr。
- 理解关闭原始文件描述符后，重定向仍然有效的原因。

## 2. 三个标准文件描述符

Linux 进程通常在启动时拥有三个标准文件描述符：

| 名称 | FD | 默认用途 |
|---|---|---|
| STDIN_FILENO | 0 | 标准输入 |
| STDOUT_FILENO | 1 | 标准输出 |
| STDERR_FILENO | 2 | 标准错误 |

对应头文件：

    #include <unistd.h>

它们本质上都是普通文件描述符，默认通常连接到终端。

## 3. dup2() 实现重定向

函数声明：

    int dup2(int oldfd, int newfd);

参数：

- oldfd：原文件描述符。
- newfd：指定的目标文件描述符。

返回值：

- 成功：返回 newfd。
- 失败：返回 -1。

当 newfd 已经打开时，dup2() 会先关闭原来的 newfd，再让它引用 oldfd 所指向的打开文件描述。

### 3.1 标准输出重定向

    dup2(fd, STDOUT_FILENO);

将标准输出 FD 1 重定向到 fd 所指向的目标。

此后：

    write(STDOUT_FILENO, "Hello\n", 6);

会将内容写入目标文件。

### 3.2 标准错误重定向

    dup2(fd, STDERR_FILENO);

将标准错误 FD 2 重定向到目标文件。

此后：

    write(STDERR_FILENO, "Error\n", 6);

会将内容写入目标文件。

### 3.3 同时重定向 stdout 和 stderr

分别打开两个文件：

    int fd1 = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int fd2 = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

执行：

    dup2(fd2, STDOUT_FILENO);
    dup2(fd1, STDERR_FILENO);

最终：

- FD 1 指向 output.txt。
- FD 2 指向 error.txt。

两个标准文件描述符分别指向不同的打开文件描述。

## 4. open() 创建重定向目标

函数声明：

    int open(const char *pathname, int flags, mode_t mode);

本日使用的标志：

| 标志 | 含义 |
|---|---|
| O_WRONLY | 只写 |
| O_CREAT | 文件不存在时创建 |
| O_TRUNC | 文件存在时清空原内容 |

权限模式：

    0644

表示创建文件时请求的权限为：

- 所有者：读、写。
- 同组用户：读。
- 其他用户：读。

头文件：

    #include <fcntl.h>
    #include <unistd.h>

## 5. 重定向后的文件描述符关系

以 stdout 重定向为例：

执行前：

    FD 1 → 终端
    fd  → output.txt

执行：

    dup2(fd, STDOUT_FILENO);

执行后：

    FD 1 → output.txt
    fd  → output.txt

此时两个文件描述符指向同一个打开文件描述。

关闭原始 fd：

    close(fd);

FD 1 仍然有效，因为它仍然引用该打开文件描述。

## 6. 本日练习

| 文件 | 内容 | 状态 |
|---|---|---|
| 01_stdout_basic.cpp | 验证标准输出和标准错误 | 完成 |
| 02_stdout_redirect.cpp | 使用 dup2() 重定向标准输出 | 完成 |
| 03_stdout_stderr_redirect.cpp | 区分 stdout 和 stderr 的输出去向 | 完成 |
| 04_stderr_redirect.cpp | 单独重定向标准错误 | 完成 |
| 05_stdout_stderr_comprehensive.cpp | 同时重定向 stdout 和 stderr | 完成 |

## 7. 本日总结

本日最重要的结论：

1. 标准输入、标准输出和标准错误分别对应 FD 0、1、2。
2. dup2() 可以将指定文件描述符复制到标准文件描述符。
3. 重定向 stdout 不会自动重定向 stderr。
4. stdout 和 stderr 可以分别指向不同文件。
5. 关闭原始文件描述符后，标准文件描述符仍然可以正常工作。

## 8. 下一阶段

Day 06：Shell 重定向。

计划学习：

- >：标准输出重定向。
- 2>：标准错误重定向。
- 2>&1：将标准错误指向标准输出当前的目标。
- 重定向操作的执行顺序。
- Shell 重定向与 dup2() 的关系。