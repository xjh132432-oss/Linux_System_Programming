# Day08 Pitfalls

## 1. execvp 的 argv 数组必须以 nullptr 结束

### 现象

执行：

    execvp("ls", args);

出现：

    execvp failed: Bad address

### 原因

execvp 要求 argv 是以空指针结束的字符串指针数组。

错误写法：

    char *args[] = {
        (char *)"ls",
        (char *)"-l"
    };

数组缺少结束标记，execvp 可能继续读取数组之外的内容。

### 正确写法

    char *args[] = {
        (char *)"ls",
        (char *)"-l",
        nullptr
    };

### 记住

exec 系列使用 argv 数组时，必须确保最后一个元素是 nullptr。

## 2. exec 失败后原程序仍然继续执行

exec 成功时不会返回。

exec 失败时返回 -1，因此必须处理失败情况：

    execvp("ls", args);

    perror("execvp failed");
    _exit(127);

不能认为调用 execvp 后，后面的代码一定不会执行。

## 3. output.txt 文件大小观察

在使用 ls -l 输出到 output.txt 的实验中，目录列表可能显示 output.txt 的大小为 0。

这是因为 ls 在写入 output.txt 之前已经读取了目录信息。

随后 ls 才将目录列表写入文件。

因此，目录列表中的文件大小是写入前观察到的状态，不代表最终文件大小。