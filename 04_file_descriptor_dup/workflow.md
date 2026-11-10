# Day 04 Workflow

## 1. 学习内容

完成 Linux 文件描述符复制相关练习。

### 01_dup_basic.cpp

- 使用 open() 打开文件。
- 使用 dup() 复制文件描述符。
- 验证 dup() 返回新的文件描述符编号。

### 02_dup_shared_offset.cpp

- 使用 dup() 创建第二个文件描述符。
- 分别通过两个描述符读取文件。
- 验证两个描述符共享文件偏移量。

### 03_dup2_basic.cpp

- 使用 dup2() 指定目标文件描述符。
- 验证 dup2() 返回指定的目标编号。
- 通过复制后的描述符读取文件。

### 04_dup_comprehensive.cpp

- 使用 open() 创建 fd1。
- 使用 dup(fd1) 创建 fd2。
- 再次 open() 创建 fd3。
- 分别读取文件，比较共享偏移量与独立偏移量。
- 关闭 fd1 后继续使用 fd2。
- 验证 fd2 仍然有效。

## 2. 验证结果

测试文件内容：

    ABCDEFGHIJ

综合练习输出：

    fd1:AB
    fd2:CD
    fd3:AB
    fd2 after close fd1:EF

实验结果符合预期。

## 3. Git 提交建议

建议提交信息：

    feat(linux): practice dup and shared file offsets

提交流程：

    git status
    git diff
    git add 04_file_descriptor_dup/
    git diff --cached
    git commit -m "feat(linux): practice dup and shared file offsets"
    git status
    git push