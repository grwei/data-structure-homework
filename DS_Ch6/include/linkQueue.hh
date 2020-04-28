/****************************************************
 * @file linkQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 链接队列的定义和实现
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_LINKQUEUE_HH_
#define INCLUDE_LINKQUEUE_HH_

#include "Queue.h"
#include <utility>

/**
 * @brief 自定义的队列类都在Queue名字空间下(linkQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief 链接队列类
 * 
 * @tparam T 数据的类型
 */
template <typename T>
class linkQueue : Queue<T>
{
public:
    /**
     * @brief 类型别名定义
     * 
     * @note 测试：能否从基类继承
     * 
     */
    typedef T value_type;                      ///< 数据类型
    typedef value_type &reference;             ///< 数据的引用
    typedef const value_type &const_reference; ///< 数据的常量引用
    typedef size_t size_type;                  ///< 计数器类型

private:
    /**
     * @brief linkQueue的结点类
     * 
     */
    struct node
    {
        /**
         * @brief 数据域
         * 
         */
        value_type _data;

        /**
         * @brief 指向后继node的指针
         * 
         */
        node *_next;

        /**
         * @brief Construct a new node object
         * 
         * @param data 数据
         * @param next 指向后继结点的指针
         */
        node(const value_type &data = value_type(), node *next = nullptr)
            : _data(data), _next(next) {}

        /**
         * @brief Construct a new node object
         * 
         * @param data 数据的值
         * @param next 指向后继结点的指针
         */
        node(value_type &&data, node *next = nullptr)
            : _data(std::move(data)), _next(next) {}

        /**
         * @brief Destroy the node object
         * 
         */
        ~node() = default;
    };

    /**
     * @brief 指向队首结点
     * 
     */
    node *_front;

    /**
     * @brief 指向队尾结点
     * 
     */
    node *_rear;

    /**
     * @brief 队列中当前元素个数
     * 
     */
    size_type _size;

public:
    /**
     * @brief Construct a new link Queue object
     * 
     */
    linkQueue();

    /**
     * @brief Destroy the link Queue object
     * 
     */
    virtual ~linkQueue();

    /**
     * @brief 判队空
     * 
     * @return true 队空
     * @return false 队非空
     */
    virtual bool isEmpty() const
    {
        return empty();
    }

    /**
     * @brief 入队一个元素
     * 
     * @param x 元素的数据
     */
    virtual void enQueue(const_reference &x)
    {
        push(x);
    }

    /**
     * @brief 出队一个元素
     * 
     * @return value_type
     */
    virtual value_type deQueue()
    {
        value_type retVal = front();
        pop();
        return retVal;
    }

    /**
     * @brief Get the Head object
     * 
     * @return value_type 队首元素的值
     */
    virtual value_type getHead() const
    {
        return front();
    }

    /**
     * @brief Test whether container is empty
     * 
     * @return true is empty
     * @return false not empty
     */
    bool empty() const;

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return size_type 
     */
    size_type size() const;

    /**
     * @brief Returns a reference to the next element in the queue.
     * 
     * @return reference& 队首元素的引用
     */
    reference &front();

    /**
     * @brief Returns a reference to the next element in the queue.
     * 
     * @return const_reference& 队首元素的常量引用
     */
    const_reference &front() const;

    /**
     * @brief Returns a reference to the last element in the queue.
     * 
     * @return reference& 队尾元素的引用
     */
    reference &back();

    /**
     * @brief Returns a reference to the last element in the queue.
     * 
     * @return const_reference& 队尾元素的常量引用
     */
    const_reference &back() const;

    /**
     * @brief Inserts a new element at the end of the queue, 
     * after its current last element.
     * 
     * @param val 数据的值
     */
    void push(const value_type &val);

    /**
     * @brief Inserts a new element at the end of the queue
     * @note after its current last element
     * 
     * @param val 数据的值
     */
    void push(value_type &&val);

    /**
     * @brief Removes the next element in the queue
     * @note effectively reducing its size by one.
     * 
     */
    void pop();
};

template <class T>
linkQueue<T>::linkQueue()
    : _front(nullptr), _rear(nullptr), _size(0)
{
}

template <class T>
linkQueue<T>::~linkQueue()
{
    node *delPtr = _front;
    while (_front)
    {
        delPtr = _front;
        _front = _front->_next;
        delete delPtr;
    }
}

template <class T>
bool linkQueue<T>::empty() const
{
    return _front == nullptr;
}

template <class T>
typename linkQueue<T>::size_type linkQueue<T>::size() const
{
    return _size;
}

template <class T>
typename linkQueue<T>::reference &linkQueue<T>::front()
{
    return _front->_data;
}

template <class T>
typename linkQueue<T>::const_reference &linkQueue<T>::front() const
{
    return _front->_data;
}

template <class T>
typename linkQueue<T>::reference &linkQueue<T>::back()
{
    return _rear->_data;
}

template <class T>
typename linkQueue<T>::const_reference &linkQueue<T>::back() const
{
    return _rear->_data;
}

template <class T>
void linkQueue<T>::push(const value_type &val)
{
    // 向空队列入队
    if (!_front)
        _rear = _front = new node(val);
    else
        _rear = _rear->_next = new node(val);
    ++_size;
}

template <class T>
void linkQueue<T>::push(value_type &&val)
{
    // 向空队列入队
    if (!_front)
        _rear = _front = new node(std::move(val));
    else
        _rear = _rear->_next = new node(std::move(val));
    ++_size;
}

template <class T>
void linkQueue<T>::pop()
{
    node *delPtr = _front;
    _front = _front->_next;
    delete delPtr;
    --_size;

    // 最后一个元素出队
    if (!_front)
        _rear = nullptr;
}

} // namespace Queue

#endif /* INCLUDE_LINKQUEUE_HH_ */
