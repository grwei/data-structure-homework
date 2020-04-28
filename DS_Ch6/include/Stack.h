/****************************************************
 * @file Stack.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief ջ�ĳ�����
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <initializer_list>
#include <utility>

namespace Stack
{

template <class T>
class Stack
{
public:
    virtual bool isEmpty() const = 0;     // ��ջ��
    virtual void push(const T &elem) = 0; // ��ջ
    virtual T pop() = 0;                  // ��ջ
    virtual T top() const = 0;            // ��ջ��Ԫ��
    virtual ~Stack() = default;
};

} // namespace Stack

#include "linkStack.hpp"
#include "seqStack.hxx"

#endif /* INCLUDE_STACK_H_ */
