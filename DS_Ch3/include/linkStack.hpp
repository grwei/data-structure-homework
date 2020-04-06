/**
 * @file linkStack.hpp
 * @author Guorui Wei (313017602@qq.com)
 * @brief 顺序栈类
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __linkStackIncluded
#define __linkStackIncluded

#include "Stack.hh"

namespace Stack
{

template <typename T>
class linkStack : public Stack<T>
{
private:
    struct node
    {
        T data;
        node *next;

        node(const T &x = T(), node *next = nullptr)
            : data(x), next(next) {}
        node(T &&x, node *next = nullptr)
            : data(std::move(x)), next(next) {}

        ~node() = default;
    };

    node *top_p; // 指向栈顶结点

public:
    linkStack();
    linkStack(std::initializer_list<T> &&il); // 支持列表初始化
    virtual bool isEmpty() const;             // 判栈空
    virtual void push(const T &elem);         // 进栈
    virtual void push(T &&elem);              // 进栈(move)
    virtual T pop();                          // 出栈
    virtual T top() const;                    // 读栈顶元素
    virtual ~linkStack();
};

template <class T>
linkStack<T>::linkStack()
    : top_p(nullptr)
{
}

template <class T>
linkStack<T>::linkStack(std::initializer_list<T> &&il)
    : linkStack()
{
    for (auto &&i : il)
        push(i);
}

template <class T>
linkStack<T>::~linkStack()
{
    while (top_p)
    {
        auto tmp = top_p->next;
        delete top_p;
        top_p = tmp;
    }
}

template <class T>
void linkStack<T>::push(const T &elem)
{
    top_p = new node(elem, top_p);
}

template <class T>
void linkStack<T>::push(T &&elem)
{
    top_p = new node(std::move(elem), top_p);
}

template <class T>
T linkStack<T>::pop()
{
    T retVal = top_p->data;

    auto tmp = top_p->next;
    delete top_p;
    top_p = tmp;

    return retVal;
}

template <class T>
T linkStack<T>::top() const
{
    return top_p->data;
}

template <class T>
bool linkStack<T>::isEmpty() const
{
    return !top_p;
}

} // namespace Stack
#endif
