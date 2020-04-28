/****************************************************
 * @file binTree.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 二叉树的抽象类
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__

namespace Tree
{

template <typename T>
class binTree
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
    virtual bool empty() const = 0;
    virtual value_type root(value_type flag) const = 0;
    virtual value_type parent(value_type x, value_type flag) const = 0;
    virtual value_type lchild(value_type x, value_type flag) const = 0;
    virtual value_type rchild(value_type x, value_type flag) const = 0;
    virtual void delLeft(value_type x) = 0;
    virtual void delRight(value_type x) = 0;
    virtual void preOrder() const = 0;
    virtual void inOrder() const = 0;
    virtual void postOrder() const = 0;
    virtual void levelOrder() const = 0;
};

} // namespace Tree

#endif // __BIN_TREE_H__
