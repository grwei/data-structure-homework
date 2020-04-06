/**
 * @file seqStack.hxx
 * @author Guorui Wei (313017602@qq.com)
 * @brief 顺序栈类的定义和实现
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __seqStackIncluded
#define __seqStackIncluded

#include "Stack.hh"
#include <climits>

namespace Stack
{

template <class T>
class seqStack : public Stack<T>
{
private:
    T *elem;            // 数组名
    int top_p;          // 栈顶元素的下标。-1表示栈空
    int maxSize;        // 数组规模
    void doubleSpace(); // 扩展空间

public:
    seqStack(int initSize = 10);
    seqStack(std::initializer_list<T> &&il); // 支持列表初始化
    virtual bool isEmpty() const;            // 判栈空
    virtual void push(const T &elem);        // 进栈
    virtual void push(T &&elem);             // 进栈(move)
    virtual T pop();                         // 出栈
    virtual T top() const;                   // 读栈顶元素
    int size() const;                        // Returns the number of elements in the stack.
    int elemMem() const;                     // 返回动态数组的大小(Bytes)
    virtual ~seqStack();
};

template <class T>
seqStack<T>::seqStack(int initSize)
    : elem(new T[initSize]), top_p(-1), maxSize(initSize)
{
}

template <class T>
seqStack<T>::seqStack(std::initializer_list<T> &&il)
    : maxSize(il.size), elem(new T[il.size]), top_p(-1)
{
    for (auto &&i : il)
        elem[++top_p] = i;
}

template <class T>
seqStack<T>::~seqStack()
{
    delete[] elem;
}

template <class T>
bool seqStack<T>::isEmpty() const
{
    return top_p == -1;
}

template <class T>
void seqStack<T>::push(const T &elem)
{
    if (top_p == maxSize - 1)
        doubleSpace();

    seqStack<T>::elem[++top_p] = elem;
}

template <class T>
void seqStack<T>::push(T &&elem)
{
    if (top_p == maxSize - 1)
        doubleSpace();

    seqStack<T>::elem[++top_p] = std::move(elem);
}

template <class T>
T seqStack<T>::pop()
{
    return elem[top_p--];
}

template <class T>
T seqStack<T>::top() const
{
    return elem[top_p];
}

template <class T>
void seqStack<T>::doubleSpace()
{
    T *old = elem;

    elem = new T[maxSize *= 2];
    for (int i = 0; i <= top_p; ++i)
        elem[i] = old[i];

    delete[] old;
}

template <class T>
int seqStack<T>::size() const
{
    return top_p + 1;
}

template <class T>
int seqStack<T>::elemMem() const
{
    return sizeof(T) * maxSize + sizeof(*this);
}

} // namespace Stack
#endif
