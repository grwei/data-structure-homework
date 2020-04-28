/****************************************************
 * @file Tree.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 树的抽象类
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include "TreeException.hh"
#include <cstddef>

/**
 * @brief 自定义的树类都在Tree名字空间内
 * 
 */
namespace Tree
{
template <typename T>
class Tree
{
public:
    /**
     * @brief 类型别名定义
     * 
     */
    typedef T value_type;                      ///< 数据类型
    typedef value_type &reference;             ///< 数据的引用
    typedef const value_type &const_reference; ///< 数据的常量引用
    typedef size_t size_type;                  ///< 计数器类型

public:
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual value_type root(value_type flag) const = 0;
    virtual value_type parent(value_type x, value_type flag) const = 0;
    virtual value_type child(value_type x, size_type i, value_type flag) const = 0;
    virtual void remove(value_type x, size_type i) = 0;
    virtual void traverse() const = 0;
};

} // namespace Tree

#include "binTree.h"
#include "binaryTree.hh"

#endif /* INCLUDE_TREE_H_ */
