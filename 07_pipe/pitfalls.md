# Day 07 Pitfalls

## 1. Here Document 没有正确结束

使用 Here Document 创建文件时：

    cat > student.txt << EOF

必须在最后单独输入一行：

    EOF

如果没有输入结束标记，Shell 会继续等待输入。不能将普通字符 q 当作 Here Document 的结束标记。

## 2. 文件名不一致

创建文件时使用的名称与后续命令中的名称必须一致。

本次实际使用的是 student.txt，而不是 students.txt。

执行命令前应确认当前目录和文件名。

## 3. 将重定向目标误写成命令

错误：

    cat student.txt | grep Alice | result.txt

result.txt 被 Shell 当作命令执行。

正确：

    cat student.txt | grep Alice > result.txt

`>` 才是将标准输出重定向到文件的操作符。

## 4. 混淆管道读端和标准输入

pipefd[0] 和 pipefd[1] 是 pipe() 明确规定的两个数组位置：

- pipefd[0]：读端。
- pipefd[1]：写端。

它们不是标准输入 FD 0 和标准输出 FD 1。

## 5. 误解空管道的 read() 行为

管道缓冲区为空时，read() 不一定返回 EOF。

- 仍有写端打开：read() 阻塞等待数据。
- 所有写端关闭：read() 返回 0，表示 EOF。

判断 EOF 时，需要考虑所有进程持有的写端是否已经关闭。

## 6. 连续调用 fork() 导致进程数量增加

如果不控制第二次 fork() 的执行分支：

    pid_t pid1 = fork();
    pid_t pid2 = fork();

第一次 fork() 创建的两个进程都会执行第二次 fork()，最终可能产生四个进程。

如果只希望创建两个子进程，需要让第二次 fork() 只在第一次 fork() 的父进程分支中执行。

## 7. read() 不会自动添加字符串结束符

read() 只读取指定数量的字节，不会自动添加 `'\0'`。

如果直接使用：

    std::cout << buffer;

输出数组内容，需要确保数组中存在有效的字符串结束符。

可以多分配一个字节，并根据 read() 返回值添加 `'\0'`。

## 8. 混淆 sizeof(buffer) 与实际读取长度

sizeof(buffer) 表示数组占用的字节数，不表示 read() 实际读取的字节数。

应该保存 read() 的返回值：

    ssize_t n = read(pipefd[0], buffer, sizeof(buffer));

使用 n 判断实际读取长度。