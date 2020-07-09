/****************************************************
 * @file seqStack.hxx
 * @author Guorui Wei (313017602@qq.com)
 * @brief ˳��ջ��Ķ����ʵ��
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

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
        T *elem;            // ������
        int top_p;          // ջ��Ԫ�ص��±ꡣ-1��ʾջ��
        int maxSize;        // �����ģ
        void doubleSpace(); // ��չ�ռ�

    public:
        seqStack(int initSize = 10);
        seqStack(std::initializer_list<T> &&il); // ֧���б���ʼ��
        virtual bool isEmpty() const;            // ��ջ��
        virtual void push(const T &elem);        // ��ջ
        virtual void push(T &&elem);             // ��ջ(move)
        virtual T pop();                         // ��ջ
        virtual T top() const;                   // ��ջ��Ԫ��
        int size() const;                        // Returns the number of elements in the stack.
        int elemMem() const;                     // ���ض�̬����Ĵ�С(Bytes)
        virtual ~seqStack();
        bool empty() const { return isEmpty(); }
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
    void seqStack<T>::push(const T &_elem)
    {
        if (top_p == maxSize - 1)
            doubleSpace();

        seqStack<T>::elem[++top_p] = _elem;
    }

    template <class T>
    void seqStack<T>::push(T &&_elem)
    {
        if (top_p == maxSize - 1)
            doubleSpace();

        seqStack<T>::elem[++top_p] = std::move(_elem);
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

#endif // __seqStackIncluded
