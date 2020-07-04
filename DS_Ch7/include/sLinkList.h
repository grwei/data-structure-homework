#ifndef __sLinkListIncluded
#define __sLinkListIncluded

#include "List.h"
#include <initializer_list>
/**
 * @file sLinkList.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 单链表类的定义和实现
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include <iostream>

namespace List
{
    // 单链表类的定义
    template <typename T>
    class sLinkList : public List<T>
    {
    private:
        struct node // 单链表中的结点类
        {
            T data;
            node *next;
            node(const T &_obj = T(), node *_next = nullptr)
                : data(_obj), next(_next) {}
            ~node() = default;
        };

        node *head;              // 头指针，指向头节点
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
            // 派生类将定义同名同参函数，仅返回类型不同。若在此（基类）设为虚函数，由于子类函数同名同参，将构成override而不是redefine。由于是值返回，override的函数必须返回相同类型以满足covariant return type规则。
            /*virtual*/ const_iterator operator++(int)
            {
                const_iterator old = *this;
                current = current->next;
                return old;
            }
            virtual bool operator==(const const_iterator &rhs) const { return rhs.current == current; }
            virtual bool operator!=(const const_iterator &rhs) const { return rhs.current != current; }
            bool isEnd() const { return !current; } // past-the-end

        protected:
            node *current;
            const_iterator(node *p) : current(p) {}

            friend sLinkList<T>;
        };

        class iterator : public const_iterator
        {
        public:
            iterator() = default;
            // 内嵌类的派生类访问基类成员须加类名限定
            virtual T &operator*() { return iterator::current->data; }
            virtual const T &operator*() const { return iterator::current->data; }
            iterator &operator++()
            {
                iterator::current = iterator::current->next;
                return *this;
            }

            // 派生类将定义同名同参函数，仅返回类型不同。若在基类设为虚函数，由于派生类函数同名同参，将构成override而不是redefine。由于是值返回，override的函数必须返回相同类型以满足covariant return type规则。
            /*virtual*/ iterator operator++(int)
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
            friend sLinkList<T>;
        };

    public:
        sLinkList() : head(new node()), currentLength(0) {}
        sLinkList(const std::initializer_list<T> &il); // 支持初始化列表
        virtual ~sLinkList()
        {
            clear();
            delete head;
        }

        virtual void clear();                     // 删除线性表中所有的元素
        virtual int length() const;               // 返回线性表的长度
        virtual void insert(int i, const T &obj); // 在第i个位置插入一个元素，即新元素的下标将为i
        virtual void remove(int i);               // 删除第i个位置的元素
        virtual int search(const T &obj) const;   // 返回元素obj在线性表中首次出现的下标
        virtual T visit(int i) const;             // 返回线性表中第i个元素
        virtual void traverse() const;            // 遍历线性表
        void erase(const T &lb, const T &rb);     // 删除所有值在[lb,rb]之间的元素
        void reverse();                           // 逆置
        T findKthLast(int k);                     // 返回倒数第k个元素，k为正整数

        virtual iterator begin() { return iterator(head->next); } // 数据范围[begin, end)
        virtual const_iterator begin() const { return iterator(head->next); }
        // 是否允许delete基类成员函数？
        virtual iterator end() = delete;
        virtual const_iterator end() const = delete;

        node &retNode() const
        {
            return *head;
        }
    };

    // 单链表类的实现
    template <class T>
    sLinkList<T>::sLinkList(const std::initializer_list<T> &il) // 支持初始化列表
        : sLinkList()
    {
        for (auto &obj : il)
            insert(currentLength, obj);
    }

    template <class T>
    typename sLinkList<T>::node *sLinkList<T>::move(int i) const
    {
        node *ptr = head;
        for (int k = 0; k <= i; ++k)
            ptr = ptr->next;

        return ptr;
    }

    template <class T>
    int sLinkList<T>::length() const
    {
        return currentLength;
    }

    template <class T>
    void sLinkList<T>::clear()
    {
        node *p{head->next}, *q;
        head = nullptr;

        while (p)
        {
            q = p->next;
            delete p;
            p = q;
        }

        currentLength = 0;
    }

    template <class T>
    void sLinkList<T>::insert(int i, const T &obj)
    {
        node *pre = move(i - 1);
        pre->next = new node(obj, pre->next);
        ++currentLength;
    }

    template <class T>
    void sLinkList<T>::remove(int i)
    {
        node *pre = move(i - 1);

        node *delp = pre->next;
        pre->next = delp->next;
        delete delp;

        --currentLength;
    }

    template <class T>
    int sLinkList<T>::search(const T &obj) const
    {
        node *ptr = head->next;
        int i = 0;

        while (ptr)
        {
            if (ptr->data == obj)
                return i;

            ptr = ptr->next;
            ++i;
        }

        return -1;
    }

    template <class T>
    T sLinkList<T>::visit(int i) const
    {
        return move(i)->data;
    }

    template <class T>
    void sLinkList<T>::traverse() const
    {
        std::cout << '\n';
        node *ptr = head->next;

        while (ptr)
        {
            std::cout << ptr->data << ' ';
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    template <class T>
    void sLinkList<T>::erase(const T &lb, const T &rb) // 删除所有值在[lb,rb]之间的元素
    {
        node *p = head; // 指向当前正在处理结点的前一结点

        while (p->next)
        {
            if (p->next->data >= lb && p->next->data <= rb)
            {
                node *delp = p->next;
                p->next = p->next->next;
                delete delp;
                --currentLength;
            }
            else
                p = p->next;
        }
    }

    template <class T>
    void sLinkList<T>::reverse() // 逆置
    {
        node *p = head->next, *q;
        head->next = nullptr;

        while (p)
        {
            q = p->next;

            p->next = head->next;
            head->next = p;
            p = q;
        }
    }

    template <class T>
    T sLinkList<T>::findKthLast(int k) // 返回倒数第k个元素，k为正整数
    {
        typename sLinkList<T>::node *p = head->next, *q = head->next;

        // 使q指向第k个结点
        for (int i = 0; i < k; ++i)
        {
            if (!q)
                return T();
            q = q->next;
        }

        //
        while (q)
        {
            p = p->next;
            q = q->next;
        }

        std::cout << '\n';
        std::cout << "The " << k << "-th last element is " << p->data << std::endl;

        return p->data;
    }
} // namespace List
#endif
