# Day 02 Pitfalls

## 1. 文件描述符不能只判断是否大于 0

### 遇到的问题

最初使用：

    if (fd > 0)

判断 `open()` 是否成功。

### 原因

文件描述符 0 也是有效的文件描述符。

如果标准输入已经关闭，后续 `open()` 可能返回 0。

### 正确写法

    if (fd >= 0)
    {
        // open 成功
    }
    else
    {
        // open 失败
    }

## 2. sizeof 字符串字面量包含末尾的空字符

### 遇到的问题

最初使用：

    write(fd, "Linux System Programming", sizeof("Linux System Programming"));

导致写入长度包含字符串末尾的 `\0`。

### 原因

字符串字面量在内存中以 `\0` 结尾。

`sizeof()` 计算的长度包含这个结束符。

### 正确写法

    write(fd, "Linux System Programming",
          sizeof("Linux System Programming") - 1);

## 3. write() 不能直接将整数地址当作数字输出

### 遇到的问题

尝试使用：

    write(STDOUT_FILENO, &fd3, 1);

希望输出文件描述符的数字。

### 原因

`&fd3` 是整数变量的内存地址。

`write()` 按字节读取该地址指向的内存内容，不会自动将整数转换成十进制字符。

### 正确写法

    std::cout << fd3 << '\n';

## 4. 文件描述符关闭后可以被重新分配

### 遇到的问题

实验中观察到：

    fd1 = 3
    fd2 = 4
    fd3 = 3

最初需要理解为什么第三次 `open()` 又返回了 3。

### 原因

Linux 通常优先分配当前进程最小的可用文件描述符。

执行 `close(fd1)` 后，编号 3 被释放，后续 `open()` 可以重新使用它。

## 5. 文件写入没有自动换行

### 遇到的问题

文件输出为：

    First lineSecond line

### 原因

两次写入的字符串都没有包含换行符 `\n`。

`write()` 不会自动添加换行。

### 正确写法

    write(fd, "First line\n", sizeof("First line\n") - 1);

    write(fd1, "Second line\n", sizeof("Second line\n") - 1);

## 6. read() 返回值必须先检查

### 遇到的问题

最初直接将 `read()` 的返回值作为 `write()` 的长度参数。

### 原因

`read()` 可能返回：

- 正数：实际读取的字节数。
- 0：到达文件末尾。
- -1：读取失败。

不能在没有检查返回值的情况下直接使用它。

### 正确处理方式

    ssize_t n = read(fd, buffer, sizeof(buffer));

    if (n > 0)
    {
        write(STDOUT_FILENO, buffer, n);
    }
    else if (n == 0)
    {
        // EOF
    }
    else
    {
        // read failed
    }

## 7. O_TRUNC 与 O_APPEND 的区别

### 实验结论

- `O_TRUNC`：打开文件时清空已有内容。
- `O_APPEND`：写入时追加到文件末尾。
- 普通 `O_WRONLY`：新打开文件的初始偏移量通常为 0，可能覆盖已有内容。

这不是程序错误，而是本日实验中需要掌握的重要行为差异。