# Day 06 - Workflow

## 1. 创建学习目录

    mkdir 06_shell_redirection
    cd 06_shell_redirection

## 2. 编写测试程序

创建 `01_output_test.cpp`，分别向标准输出和标准错误写入内容。

## 3. 编译与运行

    g++ 01_output_test.cpp -o 01_output_test
    ./01_output_test

验证程序可以同时向 stdout 和 stderr 输出。

## 4. 基础重定向实践

执行：

    ./01_output_test > out.txt
    ./01_output_test 2> err.txt
    ./01_output_test > out.txt 2> err.txt

验证标准输出和标准错误分别进入对应文件。

## 5. 追加重定向实践

执行：

    ./01_output_test >> out.txt
    ./01_output_test 2>> err.txt

验证追加操作不会清空原文件内容。

## 6. 合并重定向实践

执行：

    ./01_output_test > all.txt 2>&1
    ./01_output_test 2>&1 > all.txt

观察终端和文件的输出差异，验证重定向的执行顺序。

## 7. 本日完成情况

- 完成标准输出重定向。
- 完成标准错误重定向。
- 完成覆盖和追加重定向。
- 完成 stdout 与 stderr 分流。
- 完成 stdout 与 stderr 合并。
- 理解 `2>&1` 的文件描述符语义。
- 理解 Shell 重定向的从左到右执行规则。

## 8. 推荐 Git Commit

    feat(linux): practice shell output redirection