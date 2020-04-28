/****************************************************
 * @file linkQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief ���Ӷ��еĶ����ʵ��
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
 * @brief �Զ���Ķ����඼��Queue���ֿռ���(linkQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief ���Ӷ�����
 * 
 * @tparam T ���ݵ�����
 */
template <typename T>
class linkQueue : Queue<T>
{
public:
    /**
     * @brief ���ͱ�������
     * 
     * @note ���ԣ��ܷ�ӻ���̳�
     * 
     */
    typedef T value_type;                      ///< ��������
    typedef value_type &reference;             ///< ���ݵ�����
    typedef const value_type &const_reference; ///< ���ݵĳ�������
    typedef size_t size_type;                  ///< ����������

private:
    /**
     * @brief linkQueue�Ľ����
     * 
     */
    struct node
    {
        /**
         * @brief ������
         * 
         */
        value_type _data;

        /**
         * @brief ָ����node��ָ��
         * 
         */
        node *_next;

        /**
         * @brief Construct a new node object
         * 
         * @param data ����
         * @param next ָ���̽���ָ��
         */
        node(const value_type &data = value_type(), node *next = nullptr)
            : _data(data), _next(next) {}

        /**
         * @brief Construct a new node object
         * 
         * @param data ���ݵ�ֵ
         * @param next ָ���̽���ָ��
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
     * @brief ָ����׽��
     * 
     */
    node *_front;

    /**
     * @brief ָ���β���
     * 
     */
    node *_rear;

    /**
     * @brief �����е�ǰԪ�ظ���
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
     * @brief �жӿ�
     * 
     * @return true �ӿ�
     * @return false �ӷǿ�
     */
    virtual bool isEmpty() const
    {
        return empty();
    }

    /**
     * @brief ���һ��Ԫ��
     * 
     * @param x Ԫ�ص�����
     */
    virtual void enQueue(const_reference &x)
    {
        push(x);
    }

    /**
     * @brief ����һ��Ԫ��
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
     * @return value_type ����Ԫ�ص�ֵ
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
     * @return reference& ����Ԫ�ص�����
     */
    reference &front();

    /**
     * @brief Returns a reference to the next element in the queue.
     * 
     * @return const_reference& ����Ԫ�صĳ�������
     */
    const_reference &front() const;

    /**
     * @brief Returns a reference to the last element in the queue.
     * 
     * @return reference& ��βԪ�ص�����
     */
    reference &back();

    /**
     * @brief Returns a reference to the last element in the queue.
     * 
     * @return const_reference& ��βԪ�صĳ�������
     */
    const_reference &back() const;

    /**
     * @brief Inserts a new element at the end of the queue, 
     * after its current last element.
     * 
     * @param val ���ݵ�ֵ
     */
    void push(const value_type &val);

    /**
     * @brief Inserts a new element at the end of the queue
     * @note after its current last element
     * 
     * @param val ���ݵ�ֵ
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
    // ��ն������
    if (!_front)
        _rear = _front = new node(val);
    else
        _rear = _rear->_next = new node(val);
    ++_size;
}

template <class T>
void linkQueue<T>::push(value_type &&val)
{
    // ��ն������
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

    // ���һ��Ԫ�س���
    if (!_front)
        _rear = nullptr;
}

} // namespace Queue

#endif /* INCLUDE_LINKQUEUE_HH_ */
