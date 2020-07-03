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
#include <initializer_list>
#include <iostream>

namespace List
{
    // 顺序表类的定义
    template <typename T>
    class seqList : public List<T>
    {
    private:
        T *data;
        size_t currentLength;
        size_t maxSize;
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
        /**
         * @brief Construct a new seq List object
         * 
         * @param initSize 初始容量
         */
        seqList(size_t initSize = 10);

        /**
         * @brief Construct a new seq List object
         * 
         * @param rhs 复制源对象
         */
        seqList(const seqList<T> &rhs);

        /**
         * @brief Construct a new seq List object
         * 
         * @param rvalue 复制源对象
         */
        seqList(seqList<T> &&rvalue);

        /**
         * @brief Construct a new seq List object
         * 
         * @param init_list braced-init-list
         */
        seqList(const std::initializer_list<T> &init_list);

        /**
         * @brief Destroy the seq List object
         * 
         */
        virtual ~seqList();

        virtual void clear();                                       // 删除线性表中所有的元素
        virtual int length() const;                                 // 返回线性表的长度
        virtual void insert(int i, const T &obj);                   // 在第i个位置插入一个元素，即新元素的下标将为i
        virtual void remove(int i);                                 // 删除第i个位置的元素
        virtual int search(const T &obj) const;                     // 返回元素obj在线性表中首次出现的下标
        virtual T visit(int i) const;                               // 返回线性表中第i个元素
        virtual void traverse(std::ostream &out = std::cout) const; // 遍历线性表

        /**
         * @brief 下标访问（mutator）
         * 
         * @param index 下标
         * @return T& 元素
         */
        T &operator[](size_t index);

        /**
         * @brief 下标访问（accessor）
         * 
         * @param index 下标
         * @return const T& 元素
         */
        const T &operator[](size_t index) const;

        /**
         * @brief 在表尾插入新元素
         * 
         * @param x 新元素
         */
        void push_back(const T &x);

        /**
         * @brief 在表尾插入新元素
         * 
         * @param x 新元素
         */
        void push_back(T &&x);

        /**
         * @brief 删除表尾元素
         */
        void pop_back();

        /**
         * @brief 返回线性表的当前元素个数，即长度
         * 
         * @return size_t 当前线性表长，即元素个数
         */
        size_t size() const;

        /**
         * @brief Access first element.
         * Returns a reference to the first element in the vector.
         * 
         * @return T& A reference to the first element in the vector container.
         * If the vector object is const-qualified, the function returns a const_reference. Otherwise, it returns a reference.
         */
        T &front();

        /**
         * @brief Access first element.
         * Returns a reference to the first element in the vector.
         * 
         * @return T& A reference to the first element in the vector container.
         * If the vector object is const-qualified, the function returns a const_reference. Otherwise, it returns a reference.
         */
        const T &front() const;

        /**
         * @brief Access last element.
         * Returns a reference to the last element in the vector.
         * 
         * @return T& A reference to the last element in the vector.
         * If the vector object is const-qualified, the function returns a const_reference. Otherwise, it returns a reference.
         */
        T &back();

        /**
         * @brief Access last element.
         * Returns a reference to the last element in the vector.
         * 
         * @return T& A reference to the last element in the vector.
         * If the vector object is const-qualified, the function returns a const_reference. Otherwise, it returns a reference.
         */
        const T &back() const;

        /**
         * @brief Change size
         * Resizes the container so that it contains n elements.
         * 
         * @param n New container size, expressed in number of elements.
         */
        void resize(size_t n);

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
    size_t seqList<T>::size() const
    {
        return length();
    }

    template <class T>
    T seqList<T>::visit(int i) const
    {
        return data[i];
    }

    template <class T>
    void seqList<T>::traverse(std::ostream &out) const
    {
        out << '\n';
        for (size_t i = 0; i < currentLength; ++i)
            out << data[i] << ' ';

        out << std::endl;
    }

    template <class T>
    seqList<T>::seqList(size_t initSize)
    {
        data = new T[maxSize = initSize];
        currentLength = 0;
    }

    template <class T>
    seqList<T>::seqList(const std::initializer_list<T> &init_list)
        : currentLength{init_list.size()}, maxSize{2 * init_list.size()}
    {
        data = new T[maxSize];
        size_t i = 0;
        for (auto itr = init_list.begin(); itr != init_list.end(); ++itr)
        {
            data[i++] = *itr;
        }
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
        for (size_t i = 0; i < rhs.maxSize; ++i)
            data[i] = rhs.data[i];
    }

    template <class T>
    int seqList<T>::search(const T &obj) const
    {
        for (size_t i = 0; i < currentLength; ++i)
            if (data[i] == obj)
                return i;

        return -1;
    }

    template <class T>
    void seqList<T>::doubleSpace()
    {
        auto oldData = data;
        data = new T[maxSize *= 2];
        for (size_t i = 0; i < currentLength; ++i)
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
        size_t i = 0;
        for (size_t k = 0; k < A.length(); ++k)
            C.insert(i++, A.visit(k));

        for (size_t k = 0; k < B.length(); ++k)
            C.insert(i++, B.visit(k));

        return C;
    }

    template <class T>
    T &seqList<T>::operator[](size_t index)
    {
        if (index < 0 || index >= maxSize)
            throw(std::string{"下标越界"});
        return data[index];
    }

    template <class T>
    const T &seqList<T>::operator[](size_t index) const
    {
        if (index < 0 || index >= maxSize)
            throw(std::string{"下标越界"});
        return data[index];
    }

    template <class T>
    void seqList<T>::push_back(const T &x)
    {
        if (++currentLength > maxSize)
            doubleSpace();
        data[currentLength] = x;
    }

    template <class T>
    void seqList<T>::push_back(T &&x)
    {
        if (++currentLength > maxSize)
            doubleSpace();
        data[currentLength] = std::move(x);
    }

    template <class T>
    void seqList<T>::pop_back()
    {
        --currentLength;
    }

    template <class T>
    T &seqList<T>::front()
    {
        return data[0];
    }

    template <class T>
    const T &seqList<T>::front() const
    {
        return data[0];
    }

    template <class T>
    T &seqList<T>::back()
    {
        return data[currentLength - 1];
    }

    template <class T>
    const T &seqList<T>::back() const
    {
        return data[currentLength - 1];
    }

    template <class T>
    void seqList<T>::resize(size_t n)
    {
        if (n > maxSize)
            doubleSpace();

        currentLength = n;
    }

} // namespace List
#endif
