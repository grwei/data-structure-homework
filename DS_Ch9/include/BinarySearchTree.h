/**
 * @file BinarySearchTree.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 二叉查找树类的接口和实现
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#ifndef INCLUDE_BINARYSEARCHTREE_H_
#define INCLUDE_BINARYSEARCHTREE_H_

#include "Set.h"
#include <iostream>

namespace Set
{
    template <typename Key_T, typename Other_T = Key_T>
    class BinarySearchTree
    {
    private:
        /**
         * @brief 结点类
         * 
         */
        struct BinaryNode
        {
            Set<Key_T, Other_T> element_; ///< 数据域
            BinaryNode *left_;            ///< 左指针
            BinaryNode *right_;           ///< 右指针

            /**
             * @brief Construct a new Binary Node object
             * 
             * @param theElement 
             * @param lt 
             * @param rt 
             */
            BinaryNode(const Set<Key_T, Other_T> &theElement, BinaryNode *lt, BinaryNode *rt) : element_{theElement}, left_{lt}, right_{rt} {}
            BinaryNode(Set<Key_T, Other_T> &&theElement, BinaryNode *lt, BinaryNode *rt) : element_{std::move(theElement)}, left_{lt}, right_{rt} {}
        };

    public:
        /**
         * @brief Construct a new Binary Search Tree object
         * 
         */
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree &rhs);
        BinarySearchTree(BinarySearchTree &&rhs);
        ~BinarySearchTree();
        const Set<Key_T, Other_T> &findMin() const;
        const Set<Key_T, Other_T> &findMax() const;
        bool contains(const Key_T &x) const;
        bool isEmpty() const;
        void printTree(ostream &out = cout) const;
        void makeEmpty();
        void insert(const Set<Key_T, Other_T> &x);
        void insert(Set<Key_T, Other_T> &&x);
        void remove(const Key_T &x);
        BinarySearchTree &operator=(const BinarySearchTree &rhs);
        BinarySearchTree &operator=(BinarySearchTree &&rhs);

    private:
        BinaryNode *root;
        void insert(const Set<Key_T, Other_T> &x, BinaryNode *&t);
        void insert(Set<Key_T, Other_T> &&x, BinaryNode *&t);
        void remove(const Key_T &x, BinaryNode *&t);
        BinaryNode *findMin(BinaryNode *t) const;
        BinaryNode *findMax(BinaryNode *t) const;
        bool contains(const Key_T &x, BinaryNode *t) const;
        void makeEmpty(BinaryNode *&t);
        void printTree(BinaryNode *t, ostream &out) const;
        BinaryNode *clone(BinaryNode *t) const;
    };

} // namespace Set

#endif /* INCLUDE_BINARYSEARCHTREE_H_ */
