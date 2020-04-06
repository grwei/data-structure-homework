/**
 * @file seqList.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 顺序表类
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __seqListIncluded
#define __seqListIncluded

#include "List.h"
#include <iostream>

namespace List
{
// 顺序表类的定义
template <typename T>
class seqList : public List<T>
{
private:
    T *data;
    int currentLength;
    int maxSize;
    void doubleSpace(); // 扩大数组空间
public:
    class const_iterator
    {
    public:
        const_iterator() : current(nullptr) {}
        virtual const T &operator*() const { return *current; }
        virtual const_iterator &operator++()
        {
            ++current;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++current;
            return old;
        }
        virtual bool operator==(const const_iterator &rhs) const { return rhs.current == current; }
        virtual bool operator!=(const const_iterator &rhs) const { return rhs.current != current; }

    protected:
        T *current;

        const_iterator(T *p) : current(p) {}

        friend seqList<T>;
    };

    class iterator : public const_iterator
    {
    public:
        virtual T &operator*() { return *iterator::current; }
        virtual const T &operator*() const { return const_iterator::operator*(); } // 防止被派生类mutator覆盖
        virtual iterator &operator++()
        {
            ++iterator::current;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++iterator::current;
            return old;
        }
        // 与基类相同
        // virtual bool operator==(const iterator &rhs) const;
        // virtual bool operator!=(const iterator &rhs) const;
    protected:
        iterator(T *p) : const_iterator(p) {}

        friend seqList<T>;
    };

public:
    seqList(int initSize = 10);
    seqList(const seqList<T> &rhs);
    seqList(seqList<T> &&rvalue);
    virtual ~seqList();

    virtual void clear();                     // 删除线性表中所有的元素
    virtual int length() const;               // 返回线性表的长度
    virtual void insert(int i, const T &obj); // 在第i个位置插入一个元素，即新元素的下标将为i
    virtual void remove(int i);               // 删除第i个位置的元素
    virtual int search(const T &obj) const;   // 返回元素obj在线性表中首次出现的下标
    virtual T visit(int i) const;             // 返回线性表中第i个元素
    virtual void traverse() const;            // 遍历线性表

    virtual iterator begin() { return iterator(data); } // 数据范围[begin, end)
    virtual const_iterator begin() const { return iterator(data); }
    virtual iterator end() { return iterator(data + currentLength); }
    virtual const_iterator end() const { return iterator(data + currentLength); }
};

// 顺序表类的实现
template <class T>
seqList<T>::~seqList()
{
    delete[] data;
}

template <class T>
void seqList<T>::clear()
{
    currentLength = 0;
}

template <class T>
int seqList<T>::length() const
{
    return currentLength;
}

template <class T>
T seqList<T>::visit(int i) const
{
    return data[i];
}

template <class T>
void seqList<T>::traverse() const
{
    std::cout << '\n';
    for (int i = 0; i < currentLength; ++i)
        std::cout << data[i] << ' ';

    std::cout << std::endl;
}

template <class T>
seqList<T>::seqList(int initSize)
{
    data = new T[maxSize = initSize];
    currentLength = 0;
}

template <class T>
seqList<T>::seqList(seqList<T> &&rvalue)
    : data{rvalue.data}, currentLength{rvalue.currentLength}, maxSize{rvalue.maxSize}
{
    rvalue.data = nullptr;
    rvalue.currentLength = 0;
    rvalue.maxSize = 0;
}

template <class T>
seqList<T>::seqList(const seqList<T> &rhs)
    : data{new T[rhs.maxSize]}, currentLength{rhs.currentLength}, maxSize{rhs.maxSize}
{
    for (int i = 0; i < rhs.maxSize; ++i)
        data[i] = rhs.data[i];
}

template <class T>
int seqList<T>::search(const T &obj) const
{
    for (int i = 0; i < currentLength; ++i)
        if (data[i] == obj)
            return i;

    return -1;
}

template <class T>
void seqList<T>::doubleSpace()
{
    auto oldData = data;
    data = new T[maxSize *= 2];
    for (int i = 0; i < currentLength; ++i)
        data[i] = oldData[i];

    delete[] oldData;
}

template <class T>
void seqList<T>::insert(int i, const T &obj)
{
    if (i == currentLength)
        doubleSpace();

    for (int k = currentLength++; k > i; --k)
        data[k] = data[k - 1];

    data[i] = obj;
}

template <class T>
void seqList<T>::remove(int i)
{
    --currentLength;
    for (int k = i; i < currentLength; ++k)
        data[k] = data[k + 1];
}

template <class T>
seqList<T> operator+(const seqList<T> &A, const seqList<T> &B) // 拼接线性表
{
    seqList<T> C(A.length() + B.length());
    int i = 0;
    for (int k = 0; k < A.length(); ++k)
        C.insert(i++, A.visit(k));

    for (int k = 0; k < B.length(); ++k)
        C.insert(i++, B.visit(k));

    return C;
}
} // namespace List
#endif
