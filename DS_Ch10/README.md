# Documentation

文档

## Overview

***《数据结构：思想与实现（第2版）》（翁惠玉，俞勇）*** **第10章 排序**

- 本章文档: [排序](https://grwei.github.io/data-structure-homework/DS_Ch10/doc/html/index.html)
- 本章主页: [排序](https://grwei.github.io/data-structure-homework/DS_Ch10/)
- 课程主页: [数据结构](https://grwei.github.io/data-structure-homework/)
- 个人主页: [grwei](https://grwei.github.io/)

## 文件结构

**注意：本章所有文件的编码都是`UTF-8`**

- `./include`: 头文件
- `./src`: 测试例程
- `./doc`: `HTML`和`LATEX`文档
  - `HTML`文档[打开](./doc/html/index.html)方式：
  
  ```bat
  cd ./path/to/projectRoot
  ./doc/html/index.html
  ```

## Compiling

将`./include`文件夹加入`IncludePath`，编译`./src`文件夹中的**单个**源文件。

- **例1** `g++`编译并运行[`test0.cc`](src/test0.cc)

```bat
cd ./DS_Ch10
mkdir bin
g++ ./src/test0.cc -o ./bin/test0.exe -g -Wall -Wextra -Wshadow -static-libgcc -fexec-charset=UTF-8 -finput-charset=UTF-8 -std=c++17 -I ./include
./bin/test0.exe
```

- **例2** 编译并执行所有测试

```bat
cd ./DS_Ch10
run_test.bat
```

## References and notes

none

## Homework

- 第十章作业：
- 简答题1～7
- 程序设计题：1，2，4，7，8，10，12
- 课下思考并自己实现：3，5，6，9，11

## Contact me

- Author: Guorui Wei (危 国锐)
- E-mail: 313017602@qq.com
