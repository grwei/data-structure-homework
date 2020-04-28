/****************************************************
 * @file binTree.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief �������ĳ�����
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
     * @brief ���ͱ�������
     * 
     */
    typedef T value_type;                      ///< ��������
    typedef value_type &reference;             ///< ���ݵ�����
    typedef const value_type &const_reference; ///< ���ݵĳ�������
    typedef size_t size_type;                  ///< ����������

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
