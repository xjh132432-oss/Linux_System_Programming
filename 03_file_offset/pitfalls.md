# Day 03 - Pitfalls

记录本日实际遇到的问题及解决方法。

## 1. read() 读取的数据不能直接当作 C 字符串输出

### 问题

使用：

    read(fd, buffer, 2);
    std::cout << buffer;

输出出现乱码，例如：

    ABU��

### 原因

read() 只负责读取指定字节，不会自动在末尾添加 '\0'。

std::cout << buffer 会将 buffer 当作 C 风格字符串处理，继续寻找字符串结束符，因此可能读取到缓冲区中的无关内容。

### 解决方法

使用 std::cout.write() 按实际读取长度输出：

    ssize_t n = read(fd, buffer, 2);

    if(n > 0)
    {
        std::cout.write(buffer, n);
    }

也可以手动添加字符串结束符：

    buffer[n] = '\0';
    std::cout << buffer;

## 2. lseek() 的 offset 正负方向

### 问题

使用：

    lseek(fd, 4, SEEK_END);

本来希望读取文件末尾前面的内容，却得到 EOF。

### 原因

SEEK_END 以文件末尾为参考位置。

正数表示向文件末尾之后移动，负数表示向文件末尾之前移动。

### 解决方法

从文件末尾向前移动 4 字节：

    lseek(fd, -4, SEEK_END);

## 3. lseek() 返回值检查变量错误

### 问题

连续使用多次 lseek() 时，第二次定位后仍然检查第一次定位的返回值。

### 原因

不同次 lseek() 的返回值保存在不同变量中，检查时容易使用错误变量。

### 解决方法

分别检查对应的返回值：

    off_t pos1 = lseek(fd, 3, SEEK_CUR);

    if(pos1 == -1)
    {
        // 定位失败
    }

## 4. read() 返回值变量使用错误

### 问题

综合练习中，第二次 read() 已经保存到 n1，但 write() 使用了第一次读取的 n。

### 原因

多次读取时，容易混淆不同 read() 的返回值变量。

### 解决方法

每次读取使用对应的返回值：

    ssize_t n1 = read(fd, buffer, 4);

    if(n1 > 0)
    {
        write(STDOUT_FILENO, buffer, n1);
    }

## 5. 混合使用 std::cout 和 write() 导致输出顺序混乱

### 问题

综合练习中，混合使用：

    std::cout << "First data:";
    write(STDOUT_FILENO, buffer, n);

输出顺序与代码执行顺序不一致。

### 原因

std::cout 通常使用缓冲机制，而 write() 直接通过文件描述符输出。两套输出机制的缓冲行为不同，可能造成显示顺序混乱。

### 解决方法

统一使用 std::cout：

    std::cout << "First data:";
    std::cout.write(buffer, n);
    std::cout << '\n';

也可以在混合使用时主动刷新 std::cout 缓冲区：

    std::cout.flush();

## 6. EOF 分支没有终止后续流程

### 问题

read() 返回 0 时，虽然输出了 EOF，但程序仍然继续执行后续 lseek() 和 read()。

### 原因

判断 EOF 与终止后续操作是两件事。

### 解决方法

如果当前练习要求读取不到数据就停止，可以在 EOF 分支中关闭文件并退出。

    else if(n == 0)
    {
        write(STDOUT_FILENO, "EOF\n", 4);
        close(fd);
        return 0;
    }