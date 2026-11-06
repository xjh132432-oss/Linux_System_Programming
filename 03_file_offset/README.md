# Day 03 - File Offset & lseek

## 1. 学习目标

理解 Linux 文件 I/O 中的文件偏移量（File Offset），掌握 lseek() 的基本使用。

本日主要学习：

- 文件偏移量的含义
- read() 对文件偏移量的影响
- lseek() 的使用
- SEEK_SET、SEEK_CUR、SEEK_END 三种定位方式
- 通过文件偏移量控制读取位置

## 2. 文件偏移量

文件偏移量（File Offset）表示下一次读写操作从文件的哪个位置开始。

例如，文件内容：

    ABCDEFGHIJ

对应偏移量：

    A B C D E F G H I J
    0 1 2 3 4 5 6 7 8 9

文件刚打开时，对于普通文件，初始偏移量通常为 0。

调用 read() 读取数据后，文件偏移量会向后移动实际读取的字节数。

例如：

    read(fd, buffer, 3);

读取 ABC 后，文件偏移量从 0 变成 3。

再次读取：

    read(fd, buffer, 2);

读取 DE 后，文件偏移量从 3 变成 5。

注意：

read() 返回的是实际读取的字节数，不一定等于请求的字节数。

## 3. lseek() 函数

### 3.1 作用

lseek() 用于主动修改文件偏移量。

它只改变文件当前的读写位置，不负责读取或写入文件内容。

### 3.2 头文件

    #include <unistd.h>
    #include <sys/types.h>

### 3.3 函数声明

    off_t lseek(int fd, off_t offset, int whence);

参数：

- fd：文件描述符。
- offset：偏移量。
- whence：定位参考位置。

返回值：

- 成功：返回调整后的文件偏移量。
- 失败：返回 -1。

### 3.4 三种定位方式

#### SEEK_SET

以文件开头为参考位置。

    lseek(fd, 5, SEEK_SET);

表示将文件偏移量设置为距离文件开头 5 字节的位置。

#### SEEK_CUR

以当前文件偏移量为参考位置。

    lseek(fd, 2, SEEK_CUR);

表示在当前位置基础上向后移动 2 字节。

    lseek(fd, -2, SEEK_CUR);

表示在当前位置基础上向前移动 2 字节。

#### SEEK_END

以文件末尾为参考位置。

    lseek(fd, -4, SEEK_END);

表示从文件末尾向前移动 4 字节。

    lseek(fd, 4, SEEK_END);

表示从文件末尾向后移动 4 字节。

注意：

- 文件偏移量不能为负数。
- 普通文件允许将偏移量移动到文件末尾之后。
- 在文件末尾之后读取通常会返回 0，表示 EOF。
- lseek() 不适用于管道、FIFO 和 socket 等不可定位对象。

## 4. 文件偏移量与 read() 的关系

假设文件内容为：

    ABCDEFGHIJ

执行：

    read(fd, buffer, 3);

文件偏移量：

    0 -> 3

执行：

    lseek(fd, 2, SEEK_CUR);

文件偏移量：

    3 -> 5

再次执行：

    read(fd, buffer, 3);

读取：

    FGH

文件偏移量：

    5 -> 8

核心关系：

- read() 从当前文件偏移量开始读取。
- read() 成功读取后，会推进文件偏移量。
- lseek() 可以主动改变文件偏移量。
- lseek() 本身不读取文件内容。

## 5. 实践练习

### 01_offset_basic.cpp

练习连续调用 read()，观察文件偏移量变化。

测试文件：

    ABCDEFGHIJ

连续读取三次，每次读取 2 字节。

预期结果：

    AB
    CD
    EF

偏移量变化：

    0 -> 2 -> 4 -> 6

### 02_lseek_set.cpp

使用 SEEK_SET 定位到文件开头之后 5 字节的位置。

读取 3 字节。

预期结果：

    FGH

### 03_lseek_cur.cpp

先读取 3 字节，再使用 SEEK_CUR 向后移动 2 字节，最后读取 3 字节。

预期结果：

    ABC
    FGH

偏移量变化：

    0 -> 3 -> 5 -> 8

### 04_lseek_end.cpp

使用 SEEK_END 从文件末尾向前移动 4 字节，读取 4 字节。

测试文件：

    ABCDEFGHIJ

预期结果：

    GHIJ

### 05_lseek_comprehensive.cpp

综合使用三种定位方式。

测试文件：

    0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ

文件长度：36 字节。

第一次：

    lseek(fd, 10, SEEK_SET);

读取 5 字节：

    ABCDE

第二次：

    lseek(fd, 3, SEEK_CUR);

读取 4 字节：

    IJKL

第三次：

    lseek(fd, -5, SEEK_END);

读取 5 字节：

    VWXYZ

预期定位结果：

    First position: 10
    Second position: 18
    Third position: 31

## 6. 编译运行

以第五个练习为例：

    g++ -std=c++17 -Wall -Wextra -g 05_lseek_comprehensive.cpp -o build/05_lseek_comprehensive

    ./build/05_lseek_comprehensive

## 7. 本日总结

本日掌握：

- 文件偏移量的基本概念。
- read() 如何推进文件偏移量。
- lseek() 的函数声明、参数和返回值。
- SEEK_SET、SEEK_CUR、SEEK_END 三种定位方式。
- 连续使用 lseek() 和 read() 控制文件读取位置。

核心知识：

    lseek() 改变文件偏移量。
    read() 从当前偏移量开始读取。
    read() 的实际读取长度决定偏移量推进距离。