/****************************************************
 * @file Queue.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief ���еĳ�����
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_QUEUE_H_
#define INCLUDE_QUEUE_H_

#include <cstddef>

/**
 * @brief �Զ���Ķ����඼��Queue���ֿռ���(Queue.h)
 * 
 */
namespace Queue
{

/**
 * @brief ���еĳ�����
 * 
 * @tparam T ���ݵ�����
 */
template <typename T>
class Queue
{
public:
    /**
     * @brief ���ͱ�������
     * 
     * @note ���ԣ��ܷ�ӱ�������̳�
     * 
     */
    typedef T value_type;                      ///< ��������
    typedef value_type &reference;             ///< ���ݵ�����
    typedef const value_type &const_reference; ///< ���ݵĳ�������
    typedef size_t size_type;                  ///< ����������

public:
    /**
     * @brief �жӿ�
     * 
     * @return true �ӿ�
     * @return false �ӷǿ�
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief ���һ��Ԫ��
     * 
     * @param x ���ݵ�ֵ
     */
    virtual void enQueue(const value_type &x) = 0;

    /**
     * @brief ����һ��Ԫ��
     * 
     * @return value_type �������ݵ�ֵ
     */
    virtual value_type deQueue() = 0;

    /**
     * @brief Get the Head object
     * 
     * @return value_type ����Ԫ�ص�ֵ
     */
    virtual value_type getHead() const = 0;

    /**
     * @brief Destroy the Queue object
     * 
     */
    virtual ~Queue() = default;
};

} // namespace Queue

#include "linkQueue.hh" ///< ������ʵ�ֵĶ���
#include "seqQueue.hh"  ///< ѭ������
#include "vecQueue.hh"  ///< ��ͷλ�ù̶���˳�����

#endif /* INCLUDE_QUEUE_H_ */
