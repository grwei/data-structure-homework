#ifndef __dLinkListIncluded
#define __dLinkListIncluded

#include "List.h"
#include <iostream>

namespace List
{
// 模板使用前须先声明
template <class T>
class dLinkList;

template <class T>
dLinkList<T> operator+(const dLinkList<T> &A, const dLinkList<T> &B); // 将B拼接到A后

// 双链表类的定义
template <typename T>
class dLinkList : public List<T>
{
private:
    struct node
    {
        T data;
        node *prev, *next;

        node(const T &obj = T(), node *prev = nullptr, node *next = nullptr)
            : data(obj), prev(prev), next(next) {}
        ~node() = default;
    };

    node *head, *tail;       // 头尾指针
    int currentLength;       // 表长
    node *move(int i) const; // 返回指向第i个结点的指针，i = -1表示头指针

public:
    class const_iterator
    {
    public:
        const_iterator() : current(nullptr) {}
        virtual const T &operator*() const { return current->data; }
        virtual const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            current = current->next;
            return old;
        }
        virtual bool operator==(const const_iterator &rhs) const { return rhs.current == current; }
        virtual bool operator!=(const const_iterator &rhs) const { return rhs.current != current; }

    protected:
        node *current;
        const_iterator(node *p) : current(p) {}

        friend dLinkList<T>;
    };

    class iterator : public const_iterator
    {
    public:
        virtual T &operator*() { return iterator::current->data; }
        virtual const T &operator*() const { return iterator::current->data; }
        virtual iterator &operator++()
        {
            iterator::current = iterator::current->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            iterator::current = iterator::current->next;
            return old;
        }
        // 与基类相同
        // virtual bool operator==(const iterator &rhs) const;
        // virtual bool operator!=(const iterator &rhs) const;
    protected:
        iterator(node *p) : const_iterator(p) {}

        friend dLinkList<T>;
    };

public:
    dLinkList();
    ~dLinkList()
    {
        clear();
        delete head;
        delete tail;
    }

    virtual void clear();                                                           // 删除线性表中所有的元素
    virtual int length() const;                                                     // 返回线性表的长度
    virtual void insert(int i, const T &obj);                                       // 在第i个位置插入一个元素，即新元素的下标将为i
    virtual void remove(int i);                                                     // 删除第i个位置的元素
    virtual int search(const T &obj) const;                                         // 返回元素obj在线性表中首次出现的下标
    virtual T visit(int i) const;                                                   // 返回线性表中第i个元素
    virtual void traverse() const;                                                  // 遍历线性表
    void push_back(const T &obj);                                                   // 向表尾添加一个新元素
    friend dLinkList<T> operator+<T>(const dLinkList<T> &A, const dLinkList<T> &B); // 将B拼接到A后

    virtual iterator begin() { return iterator(head->next); } // 数据范围[begin, end)
    virtual const_iterator begin() const { return iterator(head->next); }
    // 是否允许delete基类成员函数？
    virtual iterator end() { return iterator(tail); }
    virtual const_iterator end() const { return iterator(tail); }
};

// 友元函数模板的定义
template <class T>
dLinkList<T> operator+(const dLinkList<T> &A, const dLinkList<T> &B) // 将B拼接到A后
{
    dLinkList<T> C;

    typename dLinkList<T>::node *p = A.head->next;
    while (p != A.tail)
    {
        C.push_back(p->data);
        p = p->next;
    }

    p = B.head->next;
    while (p != B.tail)
    {
        C.push_back(p->data);
        p = p->next;
    }

    return C;
}

// 双链表类的实现
template <class T>
dLinkList<T>::dLinkList()
    : head(new node()), tail(new node()), currentLength(0)
{
    head->next = tail;
    tail->prev = head;
}

template <class T>
int dLinkList<T>::length() const
{
    return currentLength;
}

template <class T>
typename dLinkList<T>::node *dLinkList<T>::move(int i) const
{
    node *ptr = head;
    for (int k = 0; k <= i; ++k)
        ptr = ptr->next;

    return ptr;
}

template <class T>
void dLinkList<T>::insert(int i, const T &obj)
{
    node *pos{move(i)};

    pos->prev = pos->prev->next = new node(obj, pos->prev, pos);

    ++currentLength;
}

template <class T>
void dLinkList<T>::remove(int i)
{
    node *delp = move(i);

    delp->prev->next = delp->next;
    delp->next->prev = delp->prev;
    delete delp;

    --currentLength;
}

template <class T>
void dLinkList<T>::clear()
{
    node *p = head->next, *q;

    head->next = tail;
    tail->prev = head;

    while (p)
    {
        q = p->next;
        delete p;
        p = q;
    }

    currentLength = 0;
}

template <class T>
int dLinkList<T>::search(const T &obj) const
{
    node *p = head->next;
    int i = 0;

    while (p != tail)
    {
        if (p->data == obj)
            return i;

        p = p->next;
        ++i;
    }

    return -1;
}

template <class T>
T dLinkList<T>::visit(int i) const
{
    return move(i)->data;
}

template <class T>
void dLinkList<T>::traverse() const
{
    std::cout << '\n';

    node *p = head->next;
    while (p != tail)
    {
        std::cout << p->data << ' ';
        p = p->next;
    }

    std::cout << std::endl;
}

template <class T>
void dLinkList<T>::push_back(const T &obj) // 向表尾添加一个新元素
{
    tail->prev = tail->prev->next = new node(obj, tail->prev, tail);
}
} // namespace List
#endif
