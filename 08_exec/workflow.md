# Day08 Workflow

## 1. 实践目录

    08_exec/
    ├── 01_fork_exec.cpp
    ├── 02_args_demo.cpp
    ├── 03.cpp
    └── CMakeLists.txt

## 2. 实践过程

### 01_fork_exec.cpp

1. 创建子进程。
2. 子进程通过 execvp 执行 ls -l。
3. exec 失败时使用 perror 输出错误。
4. 使用 _exit(127) 结束执行失败的子进程。
5. 父进程使用 waitpid 等待子进程。
6. 使用 WIFEXITED 和 WEXITSTATUS 检查退出状态。

实际验证：
- execvp 成功执行 ls。
- 使用不存在的程序名 not_exist，验证 exec 失败处理。
- 观察到错误信息 `No such file or directory`。
- 父进程成功获取退出码 127。

### 02_args_demo.cpp

1. 使用 main(argc, argv) 接收命令行参数。
2. 输出 argc。
3. 遍历 argv，输出每个参数。

实际验证命令：

    ./build/args_demo hello 123 linux

实际输出：

    argc: 4
    argv[0]: ./build/args_demo
    argv[1]: hello
    argv[2]: 123
    argv[3]: linux

### 文件描述符继承实验

1. 子进程使用 open 打开 output.txt。
2. 使用 dup2 将标准输出重定向到文件。
3. 使用 close 关闭原始文件描述符。
4. 使用 execvp 执行 ls -l。
5. 父进程使用 waitpid 等待执行完成。
6. 使用 cat 查看 output.txt。

实际验证：
- ls -l 的输出进入 output.txt。
- 终端不再直接显示 ls -l 的目录列表。
- 父进程能够继续执行并获取子进程退出状态。

## 3. Git 提交流程

    git status
    git diff
    git add 08_exec/
    git diff --cached
    git commit -m "feat(linux): practice exec and process replacement"
    git status
    git push