# Documentation

�ĵ�

## Overview

_**�����ݽṹ��˼����ʵ�֣���2�棩�����̻������£�**_ **��6�� ��**

- �����ĵ�: [��](https://grwei.github.io/data-structure-homework/DS_Ch6/doc/html/index.html)
- ������ҳ: [��](https://grwei.github.io/data-structure-homework/DS_Ch6/)
- �γ���ҳ: [���ݽṹ](https://grwei.github.io/data-structure-homework/)
- ������ҳ: [grwei](https://grwei.github.io/)

## �ļ��ṹ

**ע�⣺���������ļ��ı��붼��`GBK`**

- `./include`: ͷ�ļ�
- `./src`: ��������
- `./doc`: `HTML`��`LATEX`�ĵ�
  - `HTML`�ĵ�[��](./doc/html/index.html)��ʽ��
  
  ```bat
  cd ./path/to/projectRoot
  ./doc/html/index.html
  ```

## Compiling

��`./include`�ļ��м���`IncludePath`������`./src`�ļ����е�**����**Դ�ļ���

- **��1** `g++`���벢����[`test0.cc`](src/test0.cc)

```bat
cd ./DS_Ch6
mkdir bin
g++ ./src/test0.cc -o ./bin/test0.exe -g -Wall -Wextra -Wshadow -static-libgcc -fexec-charset=GBK -finput-charset=GBK -std=c++17 -I ./include
./bin/test0.exe
```

- **��2** ���벢ִ�����в���

```bat
cd ./DS_Ch6
run_test.bat
```

## References and notes

1. �Ӿ���·�������ļ�����Ŀ¼��[`find_last_of`](http://www.cplusplus.com/reference/string/string/find_last_of/)������[`test0.cc`](src/test0.cc)
2. ��`C/C++`����`DOS`����ɾ���ļ�������[`test0.hh`](include/test0.hh)
3. Returns the processor time consumed by the program��[`clock`](http://www.cplusplus.com/reference/ctime/clock/)������[`test0.hh`](include/test0.hh)
4. ��ȡ��ǰʱ�䣺[`localtime`](http://www.cplusplus.com/reference/ctime/localtime/)������[`test0.hh`](include/test0.hh)
5. [�ö�ջ�����ݹ��һ�㷽��](https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and)������[`binaryTree.hh`](include/binaryTree.hh)
6. ��Ҫ���ڳ�ʼ��`struct`�ĳ�Ա�������޷�ʹ��[�б��ʼ��](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#braced-initializer-list)�����Ƕ��幹�캯��������[`binaryTree.hh`](include/binaryTree.hh)(braced-initializer-list)��
    - �ο���[List initialization (since C++11)](https://en.cppreference.com/w/cpp/language/list_initialization)
7. ��������Ա������ȼ����⡣�������ȼ� `&&` > `||`����g++����ѡ���[`-Wextra`](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options)ʱ�����ܳ��� `warning: suggest parentheses around '&&' within '||'`�����gcc�ٷ��ĵ���[`-Wparentheses`](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options)
8. �����������ķǵݹ�ʵ����[�ö�ջ�����ݹ��һ�㷽��](https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and)�ļ�������̲ĸ����ķ���������һ�㷽���ļ���������Ǵ˷���ͳһ�˽̲ĸ����ĵݹ���������������[`binaryTree.hh`](include/binaryTree.hh)
   - �����ݹ���ã��ɹ�Ϊһ��stage��������һ���Խ�ջ��
   - ���޴�����tail recursions���ط�stage��ֱ�Ӱ������ջ����

9. ��ķǾ�̬���ݳ�Ա��������Ա������Ĭ��ʵ�Σ�[ԭ��](https://www.zhihu.com/question/39643639)��
10. ����ģ����ض�ʵ������ģ����ض�ʵ������Ԫ����ģ���ڵ���Ԫ�����Ƿ��ʡ��ģ��ʵ�Σ�[binaryTree.hh](include/binaryTree.hh)
    - ���ۣ����ԡ���ģ�嶨���ڣ���ģ�������ô���ģ��ʵ��Ĭ��ͬ�ඨ��ʹ�õ�ģ��ʵ�Ρ����磺

    ```cpp
    friend bool operator==</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &lhs, const binaryTree /*<T, Comparator>*/ &rhs);
    friend void printBinaryTree</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &bin_tree, const typename binaryTree /*<T, Comparator>*/ ::value_type &flag, std::ostream &out);
    ```

11. ��Ŀ���/�ƶ�����/��ֵ��������غ���
    - �ο�1��[C++���ָ�ϡ����ɿ������ͺͿ��ƶ�����](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/classes/#copyable-and-movable-types)
    - �ο�2��[C++���ģʽ����ԭ��ģʽ](https://blog.csdn.net/cabinriver/article/details/8895372?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2)
12. �������ǰ������
    �����Ǵӱ������ĽǶ�˼����˳����뵽�������ʱ���Ƿ����㹻����Ϣ��ɱ��룿
    �ο����ϣ�
    - [When can I use a forward declaration?](https://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration)
    - [Forward declaration with friend function: invalid use of incomplete type](https://stackoverflow.com/questions/3183710/forward-declaration-with-friend-function-invalid-use-of-incomplete-type?noredirect=1)
13. `std::move()`�ĺ����ʵ�α���ֵ�����ִ����Ϻ����������**���ڶ���**��
    - [�������ֹ�������ָ�ֵ�ļ򵥲���](src/ch6_6.cc)�����ƶ��Ķ�������ɿն�������������[��������](include/binaryTree.hh)�������Ϊ�����ڶ����Կɷ��ʣ����ɱ��ƶ���ֵ�����ʣ����������Ƿ���ͷ��Զ���Ա����[`BinNode *root_`](include/binaryTree.hh)

## Contact me

- Author: Guorui Wei (Σ ����)
- E-mail: 313017602@qq.com
