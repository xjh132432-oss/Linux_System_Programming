# Day 05 Workflow

## 1. 学习内容

完成标准文件描述符和 dup2() 重定向相关练习。

### 01_stdout_basic.cpp

- 使用 STDOUT_FILENO 输出普通内容。
- 使用 STDERR_FILENO 输出错误信息。
- 区分 FD 1 和 FD 2。

### 02_stdout_redirect.cpp

- 使用 open() 创建 output.txt。
- 使用 dup2() 将 FD 1 重定向到 output.txt。
- 使用 write() 向标准输出写入内容。
- 验证内容进入文件而不是终端。
- 关闭原始文件描述符。

### 03_stdout_stderr_redirect.cpp

- 将标准输出重定向到 output.txt。
- 保持标准错误连接终端。
- 分别向 stdout 和 stderr 写入内容。
- 验证两者输出去向不同。

### 04_stderr_redirect.cpp

- 使用 open() 创建 error.txt。
- 使用 dup2() 将 FD 2 重定向到 error.txt。
- 验证标准错误进入文件。
- 验证标准输出仍然进入终端。

### 05_stdout_stderr_comprehensive.cpp

- 分别打开 output.txt 和 error.txt。
- 将 FD 1 重定向到 output.txt。
- 将 FD 2 重定向到 error.txt。
- 分别写入普通输出和错误信息。
- 关闭两个原始文件描述符。
- 验证两个文件分别接收对应内容。

## 2. 验收结果

标准输出重定向：

    output.txt
    hello redirect
    This goes into a file

标准错误重定向：

    error.txt
    Error occurred

同时重定向：

    output.txt
    Normal output 1
    Normal output 2

    error.txt
    Error message 1
    Error message 2

实验结果符合预期。

## 3. Git 提交建议

建议提交信息：

    feat(linux): practice stdout and stderr redirection

提交流程：

    git status
    git diff
    git add 05_stdio_redirection/
    git diff --cached
    git commit -m "feat(linux): practice stdout and stderr redirection"
    git status
    git push