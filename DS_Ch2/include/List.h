#ifndef __ListIncluded
#define __ListIncluded

namespace List
{
// 线性表的抽象类
template <typename T>
class List
{
public:
    class const_iterator
    {
    public:
        virtual const T &operator*() const = 0;
        virtual const_iterator &operator++() = 0;
        // 不能返回抽象类，只能返回抽象类的指针或引用
        // virtual const_iterator operator++(int) = 0;
        virtual bool operator==(const const_iterator &rhs) const = 0;
        virtual bool operator!=(const const_iterator &rhs) const = 0;
    };

    class iterator : public const_iterator
    {
    public:
        virtual T &operator*() = 0;
        virtual const T &operator*() const = 0;
        virtual iterator &operator++() = 0;
        // 不允许返回抽象类，只能返回抽象类的指针或引用
        // virtual iterator operator++(int) = 0;
        virtual bool operator==(const iterator &rhs) const = 0;
        virtual bool operator!=(const iterator &rhs) const = 0;
    };

public:
    virtual void clear() = 0;                     // 删除线性表中所有的元素
    virtual int length() const = 0;               // 返回线性表的长度
    virtual void insert(int i, const T &obj) = 0; // 在第i个位置插入一个元素，即新元素的下标将为i
    virtual void remove(int i) = 0;               // 删除第i个位置的元素
    virtual int search(const T &obj) const = 0;   // 返回元素obj在线性表中首次出现的下标
    virtual T visit(int i) const = 0;             // 返回线性表中第i个元素
    virtual void traverse() const = 0;            // 遍历线性表
    virtual ~List() = default;                    // 虚析构函数，防止内存泄漏

    // 不允许返回抽象类，只能返回抽象类的指针或引用
    // virtual iterator begin() = 0; // 数据范围[begin, end)
    // virtual const_iterator begin() const = 0;
    // virtual iterator end() = 0;
    // virtual const_iterator end() const = 0;
};
} // namespace List

#include "dLinkList.h" // 双链表类的实现
#include "sLinkList.h" // 单链表类的实现
#include "seqList.h"   // 顺序表类的实现

#endif
