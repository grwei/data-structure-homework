# Documentation

文档

## Overview

_**《数据结构：思想与实现（第2版）》（翁惠玉，俞勇）**_ **第6章 树**

- 本章文档: [树](https://grwei.github.io/data-structure-homework/DS_Ch6/doc/html/index.html)
- 本章主页: [树](https://grwei.github.io/data-structure-homework/DS_Ch6/)
- 课程主页: [数据结构](https://grwei.github.io/data-structure-homework/)
- 个人主页: [grwei](https://grwei.github.io/)

## 文件结构

**注意：本章所有文件的编码都是`GBK`**

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
cd ./DS_Ch6
mkdir bin
g++ ./src/test0.cc -o ./bin/test0.exe -g -Wall -Wextra -Wshadow -static-libgcc -fexec-charset=GBK -finput-charset=GBK -std=c++17 -I ./include
./bin/test0.exe
```

- **例2** 编译并执行所有测试

```bat
cd ./DS_Ch6
run_test.bat
```

## References and notes

1. 从绝对路径解析文件所在目录：[`find_last_of`](http://www.cplusplus.com/reference/string/string/find_last_of/)，用于[`test0.cc`](src/test0.cc)
2. 用`C/C++`调用`DOS`命令删除文件，用于[`test0.hh`](include/test0.hh)
3. Returns the processor time consumed by the program：[`clock`](http://www.cplusplus.com/reference/ctime/clock/)，用于[`test0.hh`](include/test0.hh)
4. 获取当前时间：[`localtime`](http://www.cplusplus.com/reference/ctime/localtime/)，用于[`test0.hh`](include/test0.hh)
5. [用堆栈消除递归的一般方法](https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and)，用于[`binaryTree.hh`](include/binaryTree.hh)
6. 不要类内初始化`struct`的成员！否则无法使用[列表初始化](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#braced-initializer-list)，除非定义构造函数。用于[`binaryTree.hh`](include/binaryTree.hh)(braced-initializer-list)。
    - 参考：[List initialization (since C++11)](https://en.cppreference.com/w/cpp/language/list_initialization)
7. 多加括号以避免优先级问题。例如优先级 `&&` > `||`，在g++编译选项开启[`-Wextra`](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options)时，可能出现 `warning: suggest parentheses around '&&' within '||'`。详见gcc官方文档：[`-Wparentheses`](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options)
8. 二叉树遍历的非递归实现是[用堆栈消除递归的一般方法](https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and)的简化情况。教材给出的方法可视作一般方法的简单情况，于是此方法统一了教材给出的递归消除方案。用于[`binaryTree.hh`](include/binaryTree.hh)
   - 连续递归调用，可归为一个stage，按反序一次性进栈。
   - 有限次连续tail recursions不必分stage，直接按反序进栈即可

9. 类的非静态数据成员不能作成员函数的默认实参：[原因](https://www.zhihu.com/question/39643639)。
10. 函数模板的特定实例作类模板的特定实例的友元：类模板内的友元声明是否可省略模板实参？[binaryTree.hh](include/binaryTree.hh)
    - 结论：可以。类模板定义内，类模板名引用处的模板实参默认同类定义使用的模板实参。例如：

    ```cpp
    friend bool operator==</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &lhs, const binaryTree /*<T, Comparator>*/ &rhs);
    friend void printBinaryTree</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &bin_tree, const typename binaryTree /*<T, Comparator>*/ ::value_type &flag, std::ostream &out);
    ```

11. 类的拷贝/移动构造/赋值运算符重载函数
    - 参考1：[C++风格指南——可拷贝类型和可移动类型](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#copyable-and-movable-types)
    - 参考2：[C++设计模式——原型模式](https://blog.csdn.net/cabinriver/article/details/8895372?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2)
12. 关于类的前向声明
    核心是从编译器的角度思考：顺序编译到此条语句时，是否有足够的信息完成编译？
    参考资料：
    - [When can I use a forward declaration?](https://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration)
    - [Forward declaration with friend function: invalid use of incomplete type](https://stackoverflow.com/questions/3183710/forward-declaration-with-friend-function-invalid-use-of-incomplete-type?noredirect=1)
13. `std::move()`的后果：实参变右值，语句执行完毕后被析构，变成**过期对象**。
    - [关于两种构造和两种赋值的简单测试](src/ch6_6.cc)：被移动的二叉树变成空二叉树，这正是[析构函数](include/binaryTree.hh)定义的行为。过期对象仍可访问，还可被移动赋值。疑问：析构函数是否会释放自动成员？例[`BinNode *root_`](include/binaryTree.hh)

## Contact me

- Author: Guorui Wei (危 国锐)
- E-mail: 313017602@qq.com
