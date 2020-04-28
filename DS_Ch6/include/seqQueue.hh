/****************************************************
 * @file seqQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 循环队列的定义和实现
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_SEQQUEUE_HH_
#define INCLUDE_SEQQUEUE_HH_

#include "Queue.h"
#include <utility>

/**
 * @brief 自定义的队列类都在Queue名字空间下(seqQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief 循环队列类
 * 
 * @tparam T 数据的类型
 */
template <typename T>
class seqQueue : public Queue<T>
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
     * @brief 存储元素的内部数组
     * 
     */
    value_type *_elem;

    /**
     * @brief 数组的容量
     * 
     * @note 由于_elem[_front]规定为空, 故最多存储_maxSize - 1个元素
     * 
     */
    size_type _maxSize;

    /**
     * @brief 队头/尾下标
     * 数据范围(front, rear]: 在循环意义下
     * 初始状态: front == rear == 0
     * 队列满: front == (rear + 1) % maxSize
     * 队列空: front == rear
     * 
     */
    size_type _front, _rear;

    /**
     * @brief 扩大数组空间
     * 
     */
    void doubleSpace();

public:
    /**
     * @brief Construct a new seq Queue object
     * 
     * @param initSize 队列初始容量
     */
    seqQueue(size_type initSize = 10);

    /**
     * @brief Destroy the seq Queue object
     * 
     */
    virtual ~seqQueue();

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
     * @return value_type 
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
     * @brief Inserts a new element at the end of the queue, after its current last element.
     * 
     * @param val 数据的值
     */
    void push(value_type &&val);

    /**
     * @brief Removes the next element in the queue, effectively reducing its size by one.
     * 
     */
    void pop();
};

template <class T>
seqQueue<T>::seqQueue(size_type initSize)
    : _elem(new value_type[initSize]), _maxSize(initSize), _front(0), _rear(0)
{
}

template <class T>
seqQueue<T>::~seqQueue()
{
    delete[] _elem;
}

template <class T>
bool seqQueue<T>::empty() const
{
    return _front == _rear;
}

template <class T>
typename seqQueue<T>::size_type seqQueue<T>::size() const
{
    return ((_rear >= _front) ? _rear - _front : _maxSize + _rear - _front);
}

template <class T>
typename seqQueue<T>::reference &seqQueue<T>::front()
{
    return _elem[(_front + 1) % _maxSize];
}

template <class T>
typename seqQueue<T>::const_reference &seqQueue<T>::front() const
{
    return _elem[(_front + 1) % _maxSize];
}

template <class T>
typename seqQueue<T>::reference &seqQueue<T>::back()
{
    return _elem[_rear];
}

template <class T>
typename seqQueue<T>::const_reference &seqQueue<T>::back() const
{
    return _elem[_rear];
}

template <class T>
void seqQueue<T>::push(const value_type &val)
{
    if (size() == _maxSize - 1) ///< @see seqQueue<T>::_maxSize
        doubleSpace();

    _elem[_rear = (_rear + 1) % _maxSize] = val;
}

template <class T>
void seqQueue<T>::push(value_type &&val)
{
    if (size() == _maxSize - 1) ///< @see seqQueue<T>::_maxSize
        doubleSpace();

    _elem[_rear = (_rear + 1) % _maxSize] = std::move(val);
}

template <class T>
void seqQueue<T>::pop()
{
    _front = (_front + 1) % _maxSize;
}

template <class T>
void seqQueue<T>::doubleSpace()
{
    value_type *old = _elem;
    _elem = new value_type[2 * _maxSize + 1];

    for (size_type i = 1; i <= size(); ++i)
        _elem[i] = old[(_front + i) % _maxSize];
    delete[] old;

    _front = 0;
    _rear = size();
    _maxSize = 2 * _maxSize + 1;
}

} // namespace Queue

#endif /* INCLUDE_SEQQUEUE_HH_ */
