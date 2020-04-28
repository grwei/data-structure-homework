/****************************************************
 * @file Tree.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief ���ĳ�����
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
 * @brief �Զ�������඼��Tree���ֿռ���
 * 
 */
namespace Tree
{
template <typename T>
class Tree
{
public:
    /**
     * @brief ���ͱ�������
     * 
     */
    typedef T value_type;                      ///< ��������
    typedef value_type &reference;             ///< ���ݵ�����
    typedef const value_type &const_reference; ///< ���ݵĳ�������
    typedef size_t size_type;                  ///< ����������

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
