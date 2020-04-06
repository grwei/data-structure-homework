/****************************************************
 * @file Queue.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 队列的抽象类
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <cstddef>

/**
 * @brief 自定义的队列类都在Queue名字空间下(Queue.h)
 * 
 */
namespace Queue
{

/**
 * @brief 队列的抽象类
 * 
 * @tparam T 数据的类型
 */
template <typename T>
class Queue
{
public:
    /**
     * @brief 类型别名定义
     * 
     * @note 测试：能否从被派生类继承
     * 
     */
    typedef T value_type;                      ///< 数据类型
    typedef value_type &reference;             ///< 数据的引用
    typedef const value_type &const_reference; ///< 数据的常量引用
    typedef size_t size_type;                  ///< 计数器类型

public:
    /**
     * @brief 判队空
     * 
     * @return true 队空
     * @return false 队非空
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief 入队一个元素
     * 
     * @param x 数据的值
     */
    virtual void enQueue(const value_type &x) = 0;

    /**
     * @brief 出队一个元素
     * 
     * @return value_type 出队数据的值
     */
    virtual value_type deQueue() = 0;

    /**
     * @brief Get the Head object
     * 
     * @return value_type 队首元素的值
     */
    virtual value_type getHead() const = 0;

    /**
     * @brief Destroy the Queue object
     * 
     */
    virtual ~Queue() = default;
};

} // namespace Queue

#include "linkQueue.hh" ///< 单链表实现的队列
#include "seqQueue.hh"  ///< 循环队列
#include "vecQueue.hh"  ///< 队头位置固定的顺序队列

#endif
