/****************************************************
 * @file linkStack.hpp
 * @author Guorui Wei (313017602@qq.com)
 * @brief ˳��ջ��
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_LINKSTACK_HPP_
#define INCLUDE_LINKSTACK_HPP_

#include "Stack.h"

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

        node(const T &x = T(), node *_next = nullptr)
            : data(x), next(_next) {}
        node(T &&x, node *_next = nullptr)
            : data(std::move(x)), next(_next) {}

        ~node() = default;
    };

    node *top_p; // ָ��ջ�����

public:
    linkStack();
    linkStack(std::initializer_list<T> &&il); // ֧���б��ʼ��
    virtual bool isEmpty() const;             // ��ջ��
    virtual void push(const T &elem);         // ��ջ
    virtual void push(T &&elem);              // ��ջ(move)
    virtual T pop();                          // ��ջ
    virtual T top() const;                    // ��ջ��Ԫ��
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

#endif /* INCLUDE_LINKSTACK_HPP_ */
