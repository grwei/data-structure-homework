/****************************************************
 * @file vecQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 队头位置固定的顺序队列的定义和实现
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef __VECQUEUE_HH__
#define __VECQUEUE_HH__

#include "Queue.h"
#include <utility>

/**
 * @brief 自定义的队列类都在Queue名字空间下(vecQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief 队头位置固定的队列类
 * 
 * @tparam T 数据的类型
 */
template <typename T>
class vecQueue : public Queue<T>
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
     * @brief 内部数组的规模
     * 
     */
    size_type _maxSize;

    /**
     * @brief 存储队列的动态数组
     * 
     */
    value_type *_data;

    /**
     * @brief 队尾下标
     * 
     * @note 队头下标固定为0, 数据范围[0, _rear)
     * 
     */
    size_type _rear;

    /**
     * @brief 扩大数组空间
     * 
     */
    void doubleSpace();

public:
    /**
     * @brief Construct a new vec Queue object
     * 
     * @param initSize 队列初始容量
     */
    vecQueue(size_type initSize = 10);

    /**
     * @brief Destroy the vec Queue object
     * 
     */
    virtual ~vecQueue();

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
     * @return value_type 出队元素的值
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
     * @return size_type the number of elements in the queue
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
     * @brief Inserts a new element at the end of the queue, 
     * after its current last element.
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
vecQueue<T>::vecQueue(size_type initSize)
    : _maxSize(initSize), _data(new value_type[initSize]), _rear(0)
{
}

template <class T>
vecQueue<T>::~vecQueue()
{
    delete[] _data;
}

template <class T>
bool vecQueue<T>::empty() const
{
    return !_rear;
}

template <class T>
typename vecQueue<T>::size_type vecQueue<T>::size() const
{
    return _rear;
}

template <class T>
typename vecQueue<T>::reference &vecQueue<T>::front()
{
    return _data[0];
}

template <class T>
typename vecQueue<T>::const_reference &vecQueue<T>::front() const
{
    return _data[0];
}

template <class T>
typename vecQueue<T>::reference &vecQueue<T>::back()
{
    return _data[_rear - 1];
}

template <class T>
typename vecQueue<T>::const_reference &vecQueue<T>::back() const
{
    return _data[_rear - 1];
}

template <class T>
void vecQueue<T>::push(const value_type &val)
{
    if (_rear == _maxSize)
        doubleSpace();

    _data[_rear++] = val;
}

template <class T>
void vecQueue<T>::push(value_type &&val)
{
    if (_rear == _maxSize)
        doubleSpace();

    _data[_rear++] = std::move(val);
}

template <class T>
void vecQueue<T>::pop()
{
    --_rear;
    for (size_type i = 0; i < _rear; ++i)
        _data[i] = _data[i + 1];
}

template <class T>
void vecQueue<T>::doubleSpace()
{
    value_type *old = _data;
    _data = new value_type[_maxSize = 2 * _maxSize + 1];
    for (size_type i = 0; i < _rear; ++i)
        _data[i] = old[i];
    delete[] old;
}

} // namespace Queue

#endif
