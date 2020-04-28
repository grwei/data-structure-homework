/****************************************************
 * @file Stack.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 栈的抽象类
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
    virtual bool isEmpty() const = 0;     // 判栈空
    virtual void push(const T &elem) = 0; // 进栈
    virtual T pop() = 0;                  // 出栈
    virtual T top() const = 0;            // 读栈顶元素
    virtual ~Stack() = default;
};

} // namespace Stack

#include "linkStack.hpp"
#include "seqStack.hxx"

#endif /* INCLUDE_STACK_H_ */
