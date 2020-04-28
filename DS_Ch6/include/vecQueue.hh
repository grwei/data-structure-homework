/****************************************************
 * @file vecQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief ��ͷλ�ù̶���˳����еĶ����ʵ��
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_VECQUEUE_HH_
#define INCLUDE_VECQUEUE_HH_

#include "Queue.h"
#include <utility>

/**
 * @brief �Զ���Ķ����඼��Queue���ֿռ���(vecQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief ��ͷλ�ù̶��Ķ�����
 * 
 * @tparam T ���ݵ�����
 */
template <typename T>
class vecQueue : public Queue<T>
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
     * @brief �ڲ�����Ĺ�ģ
     * 
     */
    size_type _maxSize;

    /**
     * @brief �洢���еĶ�̬����
     * 
     */
    value_type *_data;

    /**
     * @brief ��β�±�
     * 
     * @note ��ͷ�±�̶�Ϊ0, ���ݷ�Χ[0, _rear)
     * 
     */
    size_type _rear;

    /**
     * @brief ��������ռ�
     * 
     */
    void doubleSpace();

public:
    /**
     * @brief Construct a new vec Queue object
     * 
     * @param initSize ���г�ʼ����
     */
    vecQueue(size_type initSize = 10);

    /**
     * @brief Destroy the vec Queue object
     * 
     */
    virtual ~vecQueue();

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
     * @return value_type ����Ԫ�ص�ֵ
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
     * @return size_type the number of elements in the queue
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
     * @brief Inserts a new element at the end of the queue, 
     * after its current last element.
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

#endif /* INCLUDE_VECQUEUE_HH_ */
