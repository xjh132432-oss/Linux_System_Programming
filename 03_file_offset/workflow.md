# Day 03 - Workflow

## 1. 学习内容

学习 Linux 文件偏移量与 lseek()。

完成的内容：

- 理解文件偏移量的含义。
- 观察连续 read() 对文件偏移量的影响。
- 学习 lseek() 函数的基本用法。
- 掌握 SEEK_SET。
- 掌握 SEEK_CUR。
- 掌握 SEEK_END。
- 完成三种定位方式的综合练习。

## 2. 实际完成的练习

### 01_offset_basic.cpp

- 打开 offset.txt。
- 连续调用三次 read()。
- 每次读取 2 字节。
- 观察文件偏移量连续推进。

### 02_lseek_set.cpp

- 使用 SEEK_SET 定位到偏移量 5。
- 读取 3 字节。
- 成功读取 FGH。
- 检查 lseek() 返回值。

### 03_lseek_cur.cpp

- 先读取 ABC。
- 使用 SEEK_CUR 向后移动 2 字节。
- 再读取 FGH。
- 理解当前位置与相对移动的关系。

### 04_lseek_end.cpp

- 使用 SEEK_END 从文件末尾向前移动 4 字节。
- 读取 GHIJ。
- 实际验证正负 offset 对定位结果的影响。

### 05_lseek_comprehensive.cpp

- 使用 SEEK_SET 定位到 10。
- 读取 ABCDE。
- 使用 SEEK_CUR 移动到 18。
- 读取 IJKL。
- 使用 SEEK_END 定位到 31。
- 读取 VWXYZ。
- 综合验证三种定位方式。

## 3. 实际完成情况

- 完成 5 个独立练习。
- 独立编写 lseek() 与 read() 组合代码。
- 对 lseek() 返回值进行错误检查。
- 对 read() 的返回值进行判断。
- 使用 write() 和 std::cout 输出读取结果。
- 排查混合输出方式造成的输出顺序问题。

## 4. 本日结果

掌握普通文件的文件偏移量操作，能够使用 lseek() 主动控制文件读取位置。