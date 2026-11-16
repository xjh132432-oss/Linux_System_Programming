# Day 06 - Pitfalls

## 1. 源文件路径错误

问题：

在仓库根目录执行：

    g++ 01_output_test.cpp -o 01_output_test

出现：

    fatal error: 01_output_test.cpp: 没有那个文件或目录

原因：

源文件位于 `06_shell_redirection/` 子目录，而不是仓库根目录。

解决：

    cd 06_shell_redirection
    g++ 01_output_test.cpp -o 01_output_test

## 2. 混淆文件描述符与普通文件名

错误写法：

    ./01_output_test 2>1& > all.txt

原因：

`2>1` 会将标准错误重定向到名为 `1` 的普通文件；`&` 则被 Shell 解释为后台执行符号。

正确写法：

    ./01_output_test 2>&1 > all.txt

注意：

- `2>1`：将 stderr 重定向到文件 1。
- `2>&1`：将 stderr 重定向到 stdout 当前指向的位置。

## 3. 混淆重定向执行顺序

以下两条命令结果不同：

    ./01_output_test > all.txt 2>&1

    ./01_output_test 2>&1 > all.txt

原因：

Shell 按从左到右的顺序处理重定向。

第一条：stdout 和 stderr 都进入文件。

第二条：stdout 进入文件，stderr 仍然进入终端。

## 4. 混淆覆盖与追加

- `>` 和 `2>` 会覆盖已有文件内容。
- `>>` 和 `2>>` 会保留原内容并追加。

执行重复测试时，需要注意文件是否被覆盖。