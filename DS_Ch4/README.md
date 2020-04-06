# Overview

**__《数据结构：思想与实现（第2版）》（翁惠玉，俞勇）第4章 队列__**

## 文件结构

* `./include`: [队列的抽象类](./include/Queue.h)，[循环队列](./include/seqQueue.hh)、[顺序队列](./include/vecQueue.hh)、[链接队列](./include/linkQueue.hh)的定义和实现。
* `./src`: 测试例程。
  * `test0.cc`：测试上述三种队列的基本功能，包括构造、入队和出队。
* `./doc`: `HTML`和`LATEX`文档
  * `HTML`文档[打开](./doc/html/index.html)方式：
  
  ```
  cd ./path/to/projectRoot
  ./doc/html/index.html
  ```

## 编译方法

将`./include`文件夹加入`IncludePath`，编译`./src`文件夹中的单个源文件。

* 以用g++编译并运行`test0.cc`为例：

```
cd ./path/to/projectRoot
mkdir bin
g++ ./src/test0.cc -o ./bin/test0.exe -g -fexec-charset=GBK -std=c++11 -I ./include
./bin/test0.exe
```

## Contact us

* Author: Guorui Wei (危 国锐)
* E-mail: 313017602@qq.com
