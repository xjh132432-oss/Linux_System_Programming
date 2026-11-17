# Day 07 - Pipe and Process Communication

## 1. Learning Objectives

本阶段主要学习 Linux 中的管道与进程基础，掌握使用匿名管道实现父子进程之间的单向通信。

完成内容：

- Shell 管道 `|`
- Shell 管道与输出重定向组合
- `pipe()` 创建匿名管道
- 进程与 PID、PPID
- `fork()` 创建子进程
- 父子进程的内存空间与文件描述符继承
- `waitpid()` 等待和回收子进程
- 使用 `pipe() + fork()` 实现父子进程通信

## 2. Shell Pipeline

### 2.1 基本概念

Shell 管道使用 `|` 连接多个命令。

前一个命令的标准输出（FD 1）连接到后一个命令的标准输入（FD 0）。

基本形式：

    command1 | command2

多个命令可以连续连接：

    command1 | command2 | command3

### 2.2 常见用法

筛选文件内容：

    cat student.txt | grep Alice

统计匹配行数：

    cat student.txt | grep Alice | wc -l

排序：

    cat student.txt | grep Alice | sort

将管道结果重定向到文件：

    cat student.txt | grep Alice > result.txt

### 2.3 管道与错误输出

默认情况下，管道只传递标准输出，不传递标准错误。

将标准错误也连接到管道：

    command 2>&1 | grep keyword

### 2.4 管道与重定向顺序

Shell 按照从左到右的顺序处理重定向。

    command > all.txt 2>&1

标准输出先重定向到文件，标准错误再复制标准输出，因此两者都进入文件。

    command 2>&1 > all.txt

标准错误先复制原来的标准输出，随后标准输出才重定向到文件，因此标准错误仍然指向原来的输出位置。

## 3. Anonymous Pipe

### 3.1 基本概念

匿名管道是 Linux 内核提供的进程间通信机制。

它具有以下特点：

- 单向字节流通信。
- 数据暂存在内核缓冲区。
- 通过文件描述符访问。
- 通常用于具有亲缘关系的进程之间通信。
- 管道本身没有消息边界。

### 3.2 pipe() API

头文件：

    #include <unistd.h>

函数原型：

    int pipe(int pipefd[2]);

参数：

- pipefd[0]：管道读端。
- pipefd[1]：管道写端。

返回值：

- 成功返回 0。
- 失败返回 -1。

基本使用：

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        return 1;
    }

向管道写入：

    write(pipefd[1], "Hello Pipe", 10);

从管道读取：

    char buffer[10];
    ssize_t n = read(pipefd[0], buffer, sizeof(buffer));

关闭管道：

    close(pipefd[0]);
    close(pipefd[1]);

### 3.3 read() 与 EOF

当管道缓冲区为空时：

- 如果仍有写端打开，read() 会阻塞等待数据。
- 如果所有写端都关闭，read() 返回 0，表示 EOF。

因此，使用管道通信时必须正确关闭不需要的文件描述符。

## 4. Process Basics

### 4.1 程序与进程

程序是存储在磁盘上的可执行文件。

进程是程序运行时的实例。

进程具有独立的虚拟地址空间、进程标识以及文件描述符表等资源。

常用命令：

    ps
    ps -ef
    echo $$

### 4.2 PID 与 PPID

- PID：当前进程的进程 ID。
- PPID：当前进程的父进程 ID。

常用 API：

    #include <unistd.h>

    pid_t getpid(void);
    pid_t getppid(void);

## 5. fork()

### 5.1 基本概念

fork() 用于创建一个新的子进程。

调用成功后，父进程和子进程都会从 fork() 返回位置继续执行。

函数原型：

    #include <unistd.h>

    pid_t fork(void);

返回值：

- -1：创建失败。
- 0：当前执行代码的是子进程。
- 大于 0：当前执行代码的是父进程，返回值为子进程 PID。

### 5.2 父子进程的区别

fork() 创建子进程后：

- 父子进程拥有各自独立的虚拟地址空间。
- 修改普通变量不会直接影响另一进程。
- 内核通过写时复制（COW）优化内存复制。
- 子进程继承父进程打开的文件描述符。
- 父子进程的执行顺序不保证固定。

### 5.3 常见 API

    pid_t getpid(void);
    pid_t getppid(void);

获取当前进程 PID 和父进程 PID。

## 6. waitpid()

### 6.1 基本概念

父进程可以使用 waitpid() 等待子进程结束，并回收子进程资源。

函数原型：

    #include <sys/wait.h>

    pid_t waitpid(pid_t pid, int *status, int options);

常用形式：

    waitpid(child_pid, nullptr, 0);

其中：

- pid：指定等待的子进程。
- status：用于获取子进程退出状态，传 nullptr 表示不接收。
- options：0 表示阻塞等待。

### 6.2 僵尸进程

子进程结束后，如果父进程没有及时回收其退出状态，子进程可能暂时处于僵尸状态。

使用 wait() 或 waitpid() 可以回收子进程资源。

## 7. Pipe + fork()

### 7.1 通信结构

先创建管道，再创建子进程：

    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

子进程会继承父进程的管道文件描述符。

本阶段采用：

- 子进程负责写入。
- 父进程负责读取。

### 7.2 文件描述符管理

父进程：

- 关闭写端 pipefd[1]。
- 使用 pipefd[0] 读取数据。
- 读取完成后关闭读端。

子进程：

- 关闭读端 pipefd[0]。
- 使用 pipefd[1] 写入数据。
- 写入完成后关闭写端。

关闭不需要的端非常重要，特别是判断 EOF 时，必须保证所有写端都已关闭。

### 7.3 通信流程

1. 父进程调用 pipe()。
2. 父进程调用 fork()。
3. 子进程关闭读端。
4. 子进程写入消息并关闭写端。
5. 父进程关闭写端。
6. 父进程读取消息。
7. 父进程调用 waitpid() 等待子进程。
8. 父进程关闭读端。

### 7.4 字符数组与 read()

read() 读取的是字节，不会自动添加字符串结束符。

如果需要将读取结果作为 C 风格字符串输出，需要预留一个字节：

    char buffer[17];

    ssize_t n = read(pipefd[0], buffer, 16);

    if (n > 0)
    {
        buffer[n] = '\0';
    }

read() 的返回值表示实际读取的字节数，不能用 sizeof(buffer) 代替。

## 8. Practice Summary

本阶段完成的实践：

- Shell 管道筛选、统计和排序。
- 管道结果重定向到文件。
- 标准错误进入管道。
- 使用 pipe() 实现同一进程中的写入和读取。
- 使用 fork() 创建子进程并观察 PID、PPID。
- 验证父子进程内存空间相互独立。
- 使用 waitpid() 等待子进程。
- 使用两次受控 fork() 创建两个子进程。
- 使用 pipe() + fork() 实现父子进程通信。

## 9. Key Takeaways

- Shell 管道将一个命令的标准输出连接到另一个命令的标准输入。
- pipe() 创建的管道具有读端和写端。
- fork() 创建子进程，父子进程从 fork() 返回位置继续执行。
- fork() 后子进程继承父进程打开的文件描述符。
- waitpid() 用于等待和回收指定子进程。
- 管道通信必须正确管理文件描述符的生命周期。
- read() 返回实际读取的字节数，不会自动添加字符串结束符。