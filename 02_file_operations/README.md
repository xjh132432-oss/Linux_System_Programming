# Day 02：Linux 文件操作基础

## 一、学习目标

掌握 Linux 下普通文件的基本操作，理解文件描述符的分配与释放机制，以及 `open()`、`close()`、`read()`、`write()` 的基本使用。

## 二、核心知识点

### 1. 文件描述符（File Descriptor）

文件描述符是进程访问已打开文件的整数编号。

Linux 进程通常默认拥有三个标准文件描述符：

| FD | 名称 | 用途 |
|---|---|---|
| 0 | STDIN_FILENO | 标准输入 |
| 1 | STDOUT_FILENO | 标准输出 |
| 2 | STDERR_FILENO | 标准错误 |

文件描述符的特点：

- `open()` 成功后返回一个文件描述符。
- `close()` 关闭文件描述符并释放对应编号。
- Linux 通常分配当前进程中最小的可用文件描述符。
- 文件描述符只是进程访问打开文件的编号，不是文件本身。

### 2. open()：打开文件

头文件：

- `<fcntl.h>`
- `<unistd.h>`

函数形式：

    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);

参数：

- `pathname`：文件路径。
- `flags`：打开标志。
- `mode`：创建文件时使用的权限参数。

返回值：

- 大于等于 0：成功，返回文件描述符。
- `-1`：失败。

### 3. 常用打开标志

| 标志 | 含义 |
|---|---|
| O_RDONLY | 只读 |
| O_WRONLY | 只写 |
| O_RDWR | 读写 |
| O_CREAT | 文件不存在时创建 |
| O_TRUNC | 以可写方式打开已有文件时清空原内容 |
| O_APPEND | 写入时追加到文件末尾 |
| O_EXCL | 配合 O_CREAT 使用，文件已存在时打开失败 |

访问模式 `O_RDONLY`、`O_WRONLY`、`O_RDWR` 三者选择其一。

多个打开标志可以通过按位或运算符 `|` 组合。

典型用法：

    open("data.txt", O_RDONLY);

    open("data.txt", O_WRONLY | O_CREAT, 0644);

    open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    open("data.txt", O_WRONLY | O_APPEND);

### 4. 文件权限

创建文件时可以使用八进制权限参数。

例如：

    open("data.txt", O_WRONLY | O_CREAT, 0644);

`0644` 的含义：

| 用户类别 | 权限 | 数值 |
|---|---|---|
| 文件所有者 | rw- | 6 |
| 所属用户组 | r-- | 4 |
| 其他用户 | r-- | 4 |

权限数值：

- r = 4：读取
- w = 2：写入
- x = 1：执行

文件创建时的最终权限还受到进程 `umask` 的影响。

查看文件权限：

    ls -l data.txt

查看当前 umask：

    umask

### 5. close()：关闭文件

头文件：

    #include <unistd.h>

函数形式：

    int close(int fd);

返回值：

- 0：成功。
- -1：失败。

文件操作完成后，应及时关闭不再使用的文件描述符。

### 6. read()：读取文件

函数形式：

    ssize_t read(int fd, void *buf, size_t count);

参数：

- `fd`：文件描述符。
- `buf`：接收读取数据的缓冲区。
- `count`：最多读取的字节数。

返回值：

- 大于 0：实际读取的字节数。
- 等于 0：到达文件末尾（EOF）。
- 等于 -1：读取失败。

注意：

- `read()` 不会自动添加字符串结束符 `\0`。
- 输出读取内容时，应使用实际读取字节数，而不是缓冲区容量。

### 7. write()：写入数据

函数形式：

    ssize_t write(int fd, const void *buf, size_t count);

参数：

- `fd`：文件描述符。
- `buf`：待写入数据的地址。
- `count`：希望写入的字节数。

返回值：

- 大于 0：实际写入的字节数。
- 等于 0：没有写入数据。
- 等于 -1：写入失败。

注意：

- `write()` 按字节写入，不会自动处理字符串。
- `sizeof("text")` 包含末尾的 `\0`。
- 写入普通文本时，可以使用 `sizeof("text") - 1`。
- `write()` 可能发生部分写入，不能认为没有返回 -1 就一定全部写入。

## 三、Day 02 实践内容

### 1. 文件创建与写入

使用：

    O_WRONLY | O_CREAT | O_TRUNC

创建文件或打开已有文件并清空内容，再通过 `write()` 写入数据。

### 2. 文件读取

使用：

    O_RDONLY

打开文件，通过 `read()` 读取数据，再通过 `write()` 输出到标准输出。

### 3. 文件描述符复用实验

连续打开文件，记录文件描述符，关闭其中一个，再次调用 `open()`。

实验观察结果：

    fd1 = 3
    fd2 = 4
    fd3 = 3

理解 Linux 通常优先分配最小可用文件描述符的规则。

### 4. 打开标志实验

通过不同的打开标志验证文件内容变化：

- `O_TRUNC`：清空原有内容。
- `O_APPEND`：在文件末尾追加。
- 普通 `O_WRONLY`：新打开文件的初始偏移量通常为 0，写入可能覆盖原有内容。

实验目标文件：`flag_test.txt`

预期内容：

    First line
    Second line

## 四、文件操作基本流程

    open()
       ↓
    获取文件描述符
       ↓
    read() / write()
       ↓
    close()

这是 Linux 文件 I/O 编程的基础操作流程。

## 五、编译方式

使用 g++ 编译：

    g++ -std=c++17 -Wall -Wextra -g source.cpp -o build/program

运行：

    ./build/program

## 六、Day 02 学习总结

本日重点不是记忆函数，而是理解：

1. 文件描述符是进程访问文件的编号。
2. `open()` 的不同标志决定文件打开和写入行为。
3. `O_TRUNC` 与 `O_APPEND` 的区别。
4. 文件权限的八进制表示。
5. `read()` 和 `write()` 返回值的意义。
6. 文件操作结束后需要关闭文件描述符。

后续学习方向：文件偏移量、`lseek()` 以及更完整的 Linux 文件 I/O 错误处理。