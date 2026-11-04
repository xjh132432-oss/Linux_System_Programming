# Day 01：文件描述符与基本 I/O

## 一、学习目标

理解 Linux 文件描述符（File Descriptor，FD）的基本概念，掌握标准输入、标准输出、标准错误，以及 read() 和 write() 两个基本 I/O 系统调用。

能够独立使用 read() 和 write() 完成简单的终端输入输出程序。

## 二、文件描述符（FD）

文件描述符是进程访问已打开 I/O 资源时使用的整数编号。

Linux 进程启动时通常具有三个标准文件描述符：

| 文件描述符 | 宏 | 含义 |
|---|---|---|
| 0 | STDIN_FILENO | 标准输入 |
| 1 | STDOUT_FILENO | 标准输出 |
| 2 | STDERR_FILENO | 标准错误 |

相关宏定义在：

- <unistd.h>

STDOUT_FILENO 与数字 1 等价，使用宏可以提高代码可读性。

## 三、read()：读取数据

### 1. 作用

read() 从指定文件描述符对应的资源读取数据，将数据存放到指定的内存缓冲区。

常见场景：

- 从终端读取键盘输入。
- 从普通文件读取数据。
- 从管道读取其他进程传递的数据。

### 2. 函数声明

    #include <unistd.h>
    #include <sys/types.h>

    ssize_t read(int fd, void *buf, size_t count);

### 3. 参数

| 参数 | 含义 |
|---|---|
| fd | 指定读取来源的文件描述符 |
| buf | 接收读取数据的缓冲区地址 |
| count | 本次最多读取的字节数 |

### 4. 返回值

返回类型：ssize_t。

| 返回值 | 含义 |
|---|---|
| 大于 0 | 实际读取的字节数 |
| 等于 0 | 到达文件末尾（EOF） |
| 等于 -1 | 读取失败 |

size_t 表示大小或长度，通常是无符号整数。

ssize_t 是有符号整数类型，可以表示负数，因此能够表示读取失败。

### 5. 使用示例

    char buffer[100];

    ssize_t bytes_read = read(
        STDIN_FILENO,
        buffer,
        sizeof(buffer)
    );

read() 不会自动在读取数据后添加字符串结束符 '\0'。

因此，处理读取结果时应使用返回值确定本次实际读取的数据长度。

例如，终端输入 hello 并按回车，在通常的终端输入模式下，可能读取到 6 字节，其中包含换行符。

## 四、write()：写入数据

### 1. 作用

write() 从指定内存区域读取数据，并将数据写入文件描述符对应的资源。

常见场景：

- 向终端输出内容。
- 向普通文件写入数据。
- 向管道写入数据。

### 2. 函数声明

    #include <unistd.h>
    #include <sys/types.h>

    ssize_t write(int fd, const void *buf, size_t count);

### 3. 参数

| 参数 | 含义 |
|---|---|
| fd | 指定写入目标的文件描述符 |
| buf | 指向待写入数据的内存地址 |
| count | 本次最多写入的字节数 |

const 表示 write() 不会通过该指针修改原始数据。

### 4. 返回值

返回类型：ssize_t。

| 返回值 | 含义 |
|---|---|
| 大于 0 | 实际写入的字节数 |
| 等于 0 | 本次没有写入字节 |
| 等于 -1 | 写入失败 |

### 5. 使用示例

    const char message[] = "Hello Linux\n";

    ssize_t bytes_written = write(
        STDOUT_FILENO,
        message,
        sizeof(message) - 1
    );

sizeof(message) 包含字符串末尾的 '\0'。

如果只需要输出字符串正文，不需要写入结束符，因此使用 sizeof(message) - 1。

write() 操作的是指定长度的字节数据，不要求缓冲区一定是以 '\0' 结尾的字符串。

## 五、read() 与 write() 对比

| 对比 | read() | write() |
|---|---|---|
| 功能 | 读取数据 | 写入数据 |
| 数据方向 | I/O 资源到内存 | 内存到 I/O 资源 |
| 参数一 | 读取来源 FD | 写入目标 FD |
| 参数二 | 数据存放位置 | 数据来源位置 |
| 参数三 | 最多读取字节数 | 最多写入字节数 |
| 返回值 | 实际读取字节数 | 实际写入字节数 |

## 六、read() 与 write() 组合

基本工作流程：

1. 使用 read() 从标准输入读取数据。
2. 将数据存入程序缓冲区。
3. 根据 read() 返回值确定实际读取长度。
4. 使用 write() 将缓冲区中的有效数据输出到标准输出。

基本代码结构：

    char buffer[100];

    ssize_t bytes_read = read(
        STDIN_FILENO,
        buffer,
        sizeof(buffer)
    );

    if (bytes_read > 0)
    {
        write(
            STDOUT_FILENO,
            buffer,
            bytes_read
        );
    }

## 七、C++ 标准 I/O 与 Linux 系统调用

| C++ 标准库 | Linux/POSIX 接口 |
|---|---|
| std::cin | read() |
| std::cout | write() |

两者都可以实现输入输出，但属于不同层次的接口。

std::cin 和 std::cout 属于 C++ 标准库。

read() 和 write() 属于 Linux/POSIX 系统编程接口。

## 八、本日总结

本日完成了文件描述符基础、标准文件描述符、read() 和 write() 的接口学习，以及两者组合使用的终端输入输出实践。

下一阶段学习 open() 和 close()，从标准文件描述符扩展到普通文件操作。