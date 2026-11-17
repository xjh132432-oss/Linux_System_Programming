# Day 07 Workflow

## 1. Shell Pipeline

创建 `07_pipe` 目录并准备学生成绩文件。

完成以下操作：

- 使用 grep 筛选 Alice 的记录。
- 使用 wc -l 统计匹配行数。
- 使用 sort 对结果排序。
- 使用 `>` 将管道结果写入文件。
- 使用 `2>&1` 将标准错误连接到管道。
- 对比不同重定向顺序的执行结果。

## 2. pipe() Practice

创建 `01_pipe_basic.cpp`。

完成以下操作：

- 使用 pipe() 创建匿名管道。
- 使用写端向管道写入数据。
- 使用读端读取数据。
- 使用 close() 关闭两个管道端。

## 3. Process and fork() Practice

学习进程、PID、PPID、fork() 和父子进程执行关系。

完成以下实践：

- `02_fork_basic.cpp`：观察父子进程 PID 和 PPID。
- `04_fork_memory.cpp`：验证父子进程普通变量相互独立。
- `05_fork_wait.cpp`：使用 waitpid() 等待子进程。
- `06_fork_multiple.cpp`：通过控制 fork() 的执行位置创建两个子进程。

## 4. Pipe + fork() Practice

创建 `03_pipe_fork.cpp`。

完成以下操作：

- 父进程创建匿名管道。
- 父进程调用 fork()。
- 子进程关闭读端并写入消息。
- 父进程关闭写端并读取消息。
- 使用 read() 返回值确定实际读取长度。
- 正确处理字符串结束符。
- 父进程使用 waitpid() 等待子进程。
- 父子进程分别关闭不需要的管道端。

## 5. Suggested Commit

    feat(linux): practice pipes and process communication

## 6. Git Workflow

    git status
    git diff
    git add 07_pipe/
    git diff --cached
    git commit -m "feat(linux): practice pipes and process communication"
    git status
    git push