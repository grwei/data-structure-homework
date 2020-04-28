/****************************************************
 * @file seqQueue.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief ѭ�����еĶ����ʵ��
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
 * @brief �Զ���Ķ����඼��Queue���ֿռ���(seqQueue.hh)
 * 
 */
namespace Queue
{

/**
 * @brief ѭ��������
 * 
 * @tparam T ���ݵ�����
 */
template <typename T>
class seqQueue : public Queue<T>
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
     * @brief �洢Ԫ�ص��ڲ�����
     * 
     */
    value_type *_elem;

    /**
     * @brief ���������
     * 
     * @note ����_elem[_front]�涨Ϊ��, �����洢_maxSize - 1��Ԫ��
     * 
     */
    size_type _maxSize;

    /**
     * @brief ��ͷ/β�±�
     * ���ݷ�Χ(front, rear]: ��ѭ��������
     * ��ʼ״̬: front == rear == 0
     * ������: front == (rear + 1) % maxSize
     * ���п�: front == rear
     * 
     */
    size_type _front, _rear;

    /**
     * @brief ��������ռ�
     * 
     */
    void doubleSpace();

public:
    /**
     * @brief Construct a new seq Queue object
     * 
     * @param initSize ���г�ʼ����
     */
    seqQueue(size_type initSize = 10);

    /**
     * @brief Destroy the seq Queue object
     * 
     */
    virtual ~seqQueue();

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
     * @brief Inserts a new element at the end of the queue, after its current last element.
     * 
     * @param val ���ݵ�ֵ
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
