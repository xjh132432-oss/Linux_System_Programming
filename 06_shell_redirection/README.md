# Day 06 - Shell Redirection

## 1. 学习目标

理解 Linux Shell 中标准输入、标准输出、标准错误的重定向机制，掌握常用重定向符号及其执行顺序。

## 2. 核心概念

### 2.1 标准文件描述符

| 文件描述符 | 名称 | 默认去向 |
|---|---|---|
| 0 | stdin | 终端输入 |
| 1 | stdout | 终端输出 |
| 2 | stderr | 终端错误输出 |

### 2.2 常用重定向符号

| 符号 | 含义 |
|---|---|
| `>` | 重定向标准输出，覆盖文件 |
| `>>` | 重定向标准输出，追加文件 |
| `2>` | 重定向标准错误，覆盖文件 |
| `2>>` | 重定向标准错误，追加文件 |
| `2>&1` | 将标准错误重定向到标准输出当前指向的位置 |

### 2.3 覆盖与追加

覆盖：

`./program > output.txt`

- 文件不存在时创建文件。
- 文件存在时清空原内容。
- 程序的标准输出进入文件。

追加：

`./program >> output.txt`

- 文件不存在时创建文件。
- 文件存在时保留原内容。
- 程序的标准输出追加到文件末尾。

### 2.4 标准输出与标准错误分流

`./program > output.txt 2> error.txt`

- stdout 进入 output.txt。
- stderr 进入 error.txt。
- 终端不显示这两种输出。

### 2.5 合并标准输出与标准错误

`./program > all.txt 2>&1`

执行顺序：

1. `> all.txt`：将 stdout 重定向到 all.txt。
2. `2>&1`：将 stderr 重定向到 stdout 当前指向的位置。

最终 stdout 和 stderr 都进入 all.txt。

### 2.6 重定向顺序

Shell 按照从左到右的顺序处理重定向。

`./program > all.txt 2>&1`

- stdout 先指向文件。
- stderr 再复制 stdout 的当前去向。
- 两者都进入文件。

`./program 2>&1 > all.txt`

- stderr 先复制 stdout 当前去向，即终端。
- stdout 再指向文件。
- stderr 仍然进入终端。

注意：`2>&1` 中的 `&` 表示后面的 `1` 是文件描述符，而不是名为 `1` 的普通文件。

## 3. 与系统调用的联系

Shell 重定向本质上与前面学习的 `open()` 和 `dup2()` 有关。

例如：

`./program > output.txt`

可以概念性地理解为：

1. Shell 使用 `open()` 打开或创建 output.txt。
2. Shell 使用 `dup2()` 将打开的文件关联到标准输出 FD 1。
3. Shell 启动程序。
4. 程序继续向 FD 1 写入，但输出已经进入文件。

示意代码：

    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    dup2(fd, STDOUT_FILENO);
    close(fd);

这里的 `0666` 是请求权限，最终权限还受到 umask 影响。

## 4. 实践内容

### 01_output_test.cpp

编写一个同时向标准输出和标准错误输出内容的测试程序。

    #include <unistd.h>

    int main()
    {
        write(STDOUT_FILENO, "Normal output\n", 14);
        write(STDERR_FILENO, "Error message\n", 14);
        return 0;
    }

编译：

    g++ 01_output_test.cpp -o 01_output_test

直接运行：

    ./01_output_test

终端同时显示：

    Normal output
    Error message

### 练习 02：基础重定向

标准输出重定向：

    ./01_output_test > output.txt

标准错误重定向：

    ./01_output_test 2> error.txt

分别重定向：

    ./01_output_test > output.txt 2> error.txt

掌握 stdout 和 stderr 的独立重定向。

### 练习 03：追加重定向

标准输出追加：

    ./01_output_test >> output.txt

标准错误追加：

    ./01_output_test 2>> error.txt

掌握覆盖与追加的区别。

### 练习 04：文件描述符合并与顺序

两种写法：

    ./01_output_test > all.txt 2>&1

    ./01_output_test 2>&1 > all.txt

观察终端和文件中的输出，理解 Shell 从左到右处理重定向的规则。

## 5. 本日总结

本日完成了 Shell 重定向的学习与实践。

掌握内容：

- 标准输出和标准错误的区别。
- `>` 与 `>>` 的区别。
- `2>` 与 `2>>` 的区别。
- 使用 `2>&1` 合并标准输出和标准错误。
- 理解重定向的执行顺序。
- 理解 Shell 重定向与 `open()`、`dup2()` 的联系。

本日核心认识：

Shell 重定向改变的是进程文件描述符的去向，程序本身不需要修改输出代码。