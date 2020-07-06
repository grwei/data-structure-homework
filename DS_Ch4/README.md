# Documentation

文档

## Overview

_**《数据结构：思想与实现（第2版）》（翁惠玉，俞勇）**_ **第4章 队列**

- 本章文档: [队列](https://grwei.github.io/data-structure-homework/DS_Ch4/doc/html/index.html)
- 本章主页: [队列](https://grwei.github.io/data-structure-homework/DS_Ch4/)
- 课程主页: [数据结构](https://grwei.github.io/data-structure-homework/)
- 个人主页: [grwei](https://grwei.github.io/)

## 文件结构

- `./include`: 头文件
  - `Queue.h`: [队列的抽象类](./include/Queue.h)
  - `seqQueue.hh`: [循环队列](./include/seqQueue.hh)
  - `vecQueue.hh`: [顺序队列](./include/vecQueue.hh)
  - `linkQueue.hh`: [链接队列](./include/linkQueue.hh)
- `./src`: 测试例程
  - `test0.cc`：[测试0](./src/test0.cc) - 测试上述三种队列的基本功能，包括构造、入队和出队。
- `./doc`: `HTML`和`LATEX`文档
  - `HTML`文档[打开](./doc/html/index.html)方式：
  
  ```bat
  cd ./path/to/projectRoot
  ./doc/html/index.html
  ```

## Compiling

将`./include`文件夹加入`IncludePath`，编译`./src`文件夹中的单个源文件。

- **例** `g++`编译并运行`test0.cc`

```bat
cd ./path/to/projectRoot
mkdir bin
g++ ./src/test0.cc -o ./bin/test0.exe -g -fexec-charset=GBK -std=c++11 -I ./include
./bin/test0.exe
```
## Homework

- 简答题1~4，
- 程序设计题：1
- 课后自行思考完成：2，3，4，5

4月11日 23:55前提交

## Contact me

- Author: Guorui Wei (危 国锐)
- E-mail: 313017602@qq.com
