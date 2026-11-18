# Day08 - exec 程序替换

## 1. 学习目标

理解 Linux 进程创建与程序替换的区别，掌握 exec 函数族，并能够组合使用：

- `fork()`：创建子进程
- `execvp()`：在子进程中执行另一个程序
- `waitpid()`：父进程等待并回收子进程
- `open()`、`dup2()`：在 exec 前重定向标准输出

## 2. 核心概念

### 2.1 fork 与 exec 的区别

`fork()` 创建一个新的子进程。

子进程继承父进程的执行状态，包括打开的文件描述符，并从 `fork()` 返回处继续执行。

`exec()` 不创建新进程，而是使用新程序替换当前进程的程序映像。

| 对比 | fork() | exec() |
|---|---|---|
| 是否创建新进程 | 是 | 否 |
| PID | 子进程获得新的 PID | 保持不变 |
| 程序映像 | 复制后独立运行 | 替换为新程序 |
| 返回行为 | 父子进程分别返回 | 成功不返回，失败返回 -1 |

### 2.2 exec 执行原理

进程映像主要包含：

- 代码段
- 数据段
- BSS 段
- 堆
- 栈
- 内存映射区域

exec 成功后，原来的用户态程序映像被替换，新程序被加载并从自己的入口开始执行。

exec 成功后：
- 原程序的代码、数据、堆和栈被新程序替换。
- PID 保持不变。
- 打开的文件描述符默认保留。
- 当前工作目录保持不变。
- 环境变量默认继承，具体取决于使用的 exec 接口。

exec 失败时返回 -1，原程序继续执行后续代码。

### 2.3 exec 函数族

头文件：

    #include <unistd.h>

| 函数 | 参数形式 | PATH 搜索 | 环境变量 |
|---|---|---|---|
| execl | 参数列表 | 否 | 继承 |
| execv | argv 数组 | 否 | 继承 |
| execle | 参数列表 | 否 | 自定义 |
| execve | argv 数组 | 否 | 自定义 |
| execlp | 参数列表 | 是 | 继承 |
| execvp | argv 数组 | 是 | 继承 |

后缀含义：

- `l`：list，参数列表
- `v`：vector，argv 数组
- `p`：通过 PATH 搜索可执行程序
- `e`：指定新的环境变量数组

示例：

    execl("/bin/ls", "ls", "-l", "-a", (char *)nullptr);

使用 argv 数组：

    char *args[] = {
        (char *)"ls",
        (char *)"-l",
        nullptr
    };

    execvp("ls", args);

注意：
- argv 数组必须以 `nullptr` 结束。
- `argv[0]` 通常表示程序名称。
- 使用 `execvp()` 时，如果程序名不包含 `/`，会通过 PATH 搜索。
- exec 成功后不会返回。

### 2.4 命令行参数

程序入口：

    int main(int argc, char *argv[])

参数说明：

- `argc`：参数数量，包含 `argv[0]`。
- `argv`：字符串指针数组，保存各个参数。
- `argv[argc]`：始终为 `nullptr`。

例如：

    ./args_demo hello 123 linux

对应：

    argc = 4

    argv[0] = "./args_demo"
    argv[1] = "hello"
    argv[2] = "123"
    argv[3] = "linux"

命令行参数默认都是字符串，需要转换后才能作为数字使用。

### 2.5 环境变量

环境变量是进程运行时使用的键值信息。

常见变量：

- PATH
- HOME
- USER
- LANG
- SHELL

使用 getenv() 获取环境变量：

    #include <cstdlib>

    char *value = getenv("PATH");

如果变量不存在，返回 `nullptr`。

exec 默认继承当前进程的环境变量。

`execle()` 和 `execve()` 可以指定新的环境变量数组：

    char *args[] = {
        (char *)"env",
        nullptr
    };

    char *envs[] = {
        (char *)"MY_NAME=Linux",
        (char *)"MY_VERSION=08",
        nullptr
    };

    execve("/usr/bin/env", args, envs);

指定环境数组时，不会自动继承原进程的全部环境变量。

### 2.6 exec 与文件描述符

exec 成功后，默认不会关闭当前进程已经打开的文件描述符。

因此，可以在 exec 之前使用 `open()` 和 `dup2()` 重定向标准输出，再执行新程序。

基本流程：

    open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execvp("ls", args);

执行过程：

1. open 打开目标文件。
2. dup2 将标准输出 FD 1 重定向到目标文件。
3. close 关闭原始 fd。
4. execvp 替换程序映像。
5. 新程序继续使用重定向后的标准输出。

这也是 Shell 输出重定向的底层基础之一。

### 2.7 FD_CLOEXEC

默认情况下，文件描述符会保留到 exec 之后。

如果不希望某个文件描述符被新程序继承，可以设置 close-on-exec 标志。

使用 fcntl：

    fcntl(fd, F_SETFD, FD_CLOEXEC);

也可以在 open 时使用：

    int fd = open("output.txt",
                  O_WRONLY | O_CREAT | O_CLOEXEC,
                  0644);

设置后，该文件描述符会在成功 exec 时自动关闭。

### 2.8 fork + exec + waitpid

这是执行外部程序的经典流程：

    fork()
      |
    子进程
      |
    exec()
      |
    执行新程序

    父进程
      |
    waitpid()
      |
    等待并回收子进程

子进程执行 exec 失败后，可以使用：

    perror("exec failed");
    _exit(127);

`_exit()` 不会执行 C/C++ 标准库的正常退出清理，也不会刷新用户态 stdio 缓冲区。

父进程使用 waitpid 获取子进程状态：

    int status;
    waitpid(pid, &status, 0);

判断是否正常退出：

    if (WIFEXITED(status)) {
        std::cout << WEXITSTATUS(status) << '\n';
    }

常用状态宏：

| 宏 | 含义 |
|---|---|
| WIFEXITED(status) | 是否正常退出 |
| WEXITSTATUS(status) | 获取正常退出时的退出码 |
| WIFSIGNALED(status) | 是否被信号终止 |
| WTERMSIG(status) | 获取终止进程的信号编号 |

注意：不能直接把 `status` 当成退出码。

## 3. 实践内容

### 01_fork_exec.cpp

实现内容：

- 使用 fork 创建子进程。
- 子进程使用 execvp 执行 `ls -l`。
- exec 失败时使用 perror 输出错误。
- 子进程使用 `_exit(127)` 退出。
- 父进程使用 waitpid 等待子进程。
- 使用 WIFEXITED 和 WEXITSTATUS 检查退出状态。

验证结果：

- exec 成功时，执行目标程序。
- exec 失败时，输出错误信息，退出码为 127。
- 父进程能够等待并回收子进程。

### 02_args_demo.cpp

实现内容：

- 使用 argc 获取参数数量。
- 使用 argv 遍历命令行参数。
- 验证 argv[0] 是程序启动路径。
- 验证命令行参数以字符串形式传递。

验证命令：

    ./build/args_demo hello 123 linux

验证结果：

    argc: 4
    argv[0]: ./build/args_demo
    argv[1]: hello
    argv[2]: 123
    argv[3]: linux

### 03.cpp

实现内容：

- fork 创建子进程。
- 子进程使用 open 打开 output.txt。
- 使用 dup2 将 stdout 重定向到文件。
- 关闭原始文件描述符。
- 使用 execvp 执行 ls -l。
- 父进程等待子进程结束。

验证结果：

- 终端不再显示 ls -l 的目录列表。
- output.txt 保存 ls -l 的输出。
- 父进程仍能正常获取子进程退出状态。

## 4. 本日总结

本日完成了从进程创建到程序替换的学习。

核心知识链：

    fork
      |
    exec
      |
    新程序运行
      |
    waitpid

并将之前学习的文件描述符、open、dup2 和 Shell 重定向联系起来。

至此，已经掌握 Linux 中执行外部程序的基本机制。