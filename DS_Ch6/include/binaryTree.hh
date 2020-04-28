/****************************************************
 * @file binaryTree.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 二叉树的二叉链表实现
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_BINARYTREE_HH_
#define INCLUDE_BINARYTREE_HH_

#include "Queue.h"
#include "Stack.h"
#include "TreeException.hh"
#include "binTree.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <utility>

namespace Tree
{
/**
 * @brief 用二叉链表实现的二叉树类
 * 
 * @tparam T 数据类型
 * @tparam Comparator 数据类型的比较器类，默认为std::less<T> 
 * 
 * @details 若类型T重载了operator<，则Comparator的默认类型std::less<T>将调用operator<，故实例化时不必指定tparam2；\n
 * 否则，要求指定模板参数Comparator，which is a function object, 重载了bool operator(T t1, T t2)：当语义上t1 < t2时返回true。
 * @details 要求对T重载了operator<< 和 operator>>。建议每个对象的输出在一行以内
 * @warning 若树中存储了data相同的结点，则私有find方法调用该方法的公有方法可能出现异常！
 */
template <typename T, typename Comparator = std::less<T>>
class binaryTree;

/**
 * @brief 输出一棵二叉树
 * 
 * @tparam T 二叉树的数据类型
 * @param bin_tree 二叉树类的对象
 * @param flag 用于表示空结点的特殊标记
 * @param out 输出流对象。默认是std::cout，也可以是ostream类及其派生类的对象，包括输出文件流等。
 * 
 * @details 按层次顺序输出每个结点及其children，用于测试二叉树类实现的正确性。
 * 该函数假定树中没有data相同的结点
 * @note 该函数模板被声明为binaryTree<T>类的友元仅作测试用，实际上不必作友元。\n
 * 用于测试：
 * -# 二叉树类实现的正确性，包括lchild，rchild，root等API
 * -# 模板作同参模板的友元
 * -# 模板函数的模板实参的推断：tparam2是否能由binaryTree的tparam2的默认值推断？
 * @deprecated 该函数仅作测试用，将在正式版本中删除。
 * @bug bin_tree中不允许含有data相同的结点，否则可能导致无限循环！
 */
template <class T, typename Comparator>
void printBinaryTree(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout);

/**
 * @brief 比较两棵二叉树是否相同
 * "相同"是指：
 * @tparam T 数据类型
 * @tparam Comparator 数据类型的比较器类，默认为std::less<T>
 * @note 此函数模板的模板实参由函数实参表推断，用户无需指定
 * @details 若类型T重载了operator<，则Comparator的默认类型std::less<T>将调用operator<，故实例化时不必指定tparam2；\n
 * 否则，要求指定模板参数Comparator，which is a function object, 重载了bool operator(T t1, T t2)：当语义上t1 < t2时返回true。
 * @param lhs 二叉树#1
 * @param rhs 二叉树#2
 * @return true #1和#2相同
 * @return false #1和#2不同
 */
template <class T, typename Comparator>
bool operator==(const binaryTree<T, Comparator> &lhs, const binaryTree<T, Comparator> &rhs);

template <typename T, typename Comparator>
class binaryTree /* : binTree<T> */
{
    /**
     * 不能在此声明下述友元(invalid use of incomplete type)，
     * 原因：类的内部类型value_type未声明。
     * 只需把友元声明置于typedef后即可
     */
    // friend void printBinaryTree</*T, Comparator*/>(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out);
    friend bool operator==</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &lhs, const binaryTree /*<T, Comparator>*/ &rhs);

public:
    /**
     * @brief 类型别名定义
     * 
     */
    typedef T value_type;                      ///< 数据类型
    typedef value_type &reference;             ///< 数据的引用
    typedef const value_type &const_reference; ///< 数据的常量引用
    typedef size_t size_type;                  ///< 计数器类型

    friend void printBinaryTree</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &bin_tree, const typename binaryTree /*<T, Comparator>*/ ::value_type &flag, std::ostream &out);

private:
    /**
     * @brief 二叉链表的结点类
     * 
     */
    struct BinNode
    {
        value_type data; ///< 数据
        BinNode *left;   ///< 指向左child
        BinNode *right;  ///< 指向右child

        /**
         * @brief Construct a new Bin Node object
         * 
         * @param _data 数据
         * @param _left 左child的地址
         * @param _right 右child的地址
         */
        explicit BinNode(const value_type &_data = value_type{}, BinNode *_left = nullptr, BinNode *_right = nullptr) : data(_data), left(_left), right(_right) {}

        /**
         * @brief Construct a new Bin Node object
         * 
         * @param _data 数据
         * @param _left 左child的地址
         * @param _right 右child的地址
         */
        explicit BinNode(value_type &&_data, BinNode *_left, BinNode *_right) : data(std::move(_data)), left(_left), right(_right) {}

        /**
         * @brief Destroy the Bin Node object
         * 
         */
        ~BinNode() = default;
    };

    BinNode *root_; ///< 二叉树的根结点

public:
    /**
     * @brief Construct a new binary Tree object
     * 
     * 创建一棵空树
     * 
     */
    binaryTree() : root_(nullptr){};

    /**
     * @brief Construct a new binary Tree object
     * 
     * 创建一棵带有根节点的树
     * 
     * @param x 根结点的数据
     */
    explicit binaryTree(const value_type &x) : root_(new BinNode(x)) {}

    /**
     * @brief Construct a new binary Tree object
     * 拷贝构造函数
     * @param rhs 源对象
     * @note 参考C++设计模式——原型模式
     */
    binaryTree(const binaryTree &rhs) : binaryTree() { root_ = clone(rhs.root_); }

    /**
     * @brief 赋值运算符重载
     * 
     * @param rhs 源对象
     * @return binaryTree& 目的对象的引用
     */
    binaryTree &operator=(const binaryTree &rhs)
    {
        // 这种模式可消除对自身赋值的特殊情况
        binaryTree copy = rhs;  // 要调用复制构造函数
        std::swap(*this, copy); // 要调用移动构造、移动赋值函数
        return *this;
    }

    /**
     * @brief Construct a new binary Tree object
     * 移动构造函数
     * @param rhs 源对象，右值
     */
    binaryTree(binaryTree &&rhs) : root_{rhs.root_} { rhs.root_ = nullptr; }

    /**
     * @brief 移动赋值运算符
     * 
     * @param rhs 源对象，右值
     * @return binaryTree& 目的对象的引用
     */
    binaryTree &operator=(binaryTree &&rhs)
    {
        // 防止自身赋值
        if (rhs.root_ == root_)
            return *this;
        std::swap(root_, rhs.root_); // 交换后，原由左操作数维护的资源转至右操作数，从而将被释放
        return *this;
    }

    /**
     * @brief Destroy the binary Tree object
     * 
     */
    ~binaryTree();

    /**
     * @brief 清空二叉树
     * 函数返回后，对象的成员root_将被置nullptr
     */
    void clear();

    /**
     * @brief 判断二叉树是否为空树
     * 
     * @return true 是空树
     * @return false 非空树
     */
    bool empty() const;

    /**
     * @brief 返回根结点的数据
     * 
     * @param flag 为空树时返回的特殊标记
     * @return value_type 根结点的数据
     */
    value_type root(const value_type &flag) const;

    /**
     * @brief 获得数据为x的结点的左child
     * 
     * @param x 目标结点的数据
     * @param flag 无左child时返回的标记
     * @return value_type 左child的数据
     * @warning 树中有data相同的结点时，该方法只能访问到前序序列中首次出现该数据的那个结点！
     */
    value_type lchild(const value_type &x, const value_type &flag) const;

    /**
     * @brief 获得数据为x的结点的右child
     * 
     * @param x 目标结点的数据
     * @param flag 无右child时返回的标记
     * @return value_type 右child的数据
     * @warning 树中有data相同的结点时，该方法只能访问到前序序列中首次出现该数据的那个结点！
     */
    value_type rchild(const value_type &x, const value_type &flag) const;

    /**
     * @brief 删除左subtree
     * 
     * @param x 目标结点。以该结点的左child为根的树将被删除
     * @warning 树中有data相同的结点时，该方法只能访问到前序序列中首次出现该数据的那个结点！
     */
    void delLeft(const value_type &x);

    /**
     * @brief 删除右subtree
     * 
     * @param x 目标结点。以该节点的右child为根的树将被删除
     * @warning 树中有data相同的结点时，该方法只能访问到前序序列中首次出现该数据的那个结点！
     */
    void delRight(const value_type &x);

    /**
     * @brief 前序遍历(递归版本)
     * 
     * 前序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void preOrder(std::ostream &out = std::cout) const;

    /**
     * @brief 前序遍历(非递归版本)
     * 
     * 前序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void preOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief 中序遍历(递归版本)
     * 
     * 中序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void inOrder(std::ostream &out = std::cout) const;

    /**
     * @brief 中序遍历(非递归版本)
     * 
     * 中序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void inOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief 后序遍历(递归版本)
     * 
     * 后序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void postOrder(std::ostream &out = std::cout) const;

    /**
     * @brief 后序遍历(非递归版本)
     * 
     * 后序打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void postOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief 层次遍历
     * 
     * 层次打印二叉树各结点的数据到标准输出设备
     * @param out 输出流对象，可以是标准输出流或文件流等
     */
    void levelOrder(std::ostream &out = std::cout) const;

    /**
     * @brief Create a Tree object
     * 
     * @param flag "空结点"的特殊标记
     * @param in 输入流对象，可以是cin, 或者ifstream类的对象等
     * 
     * @ details 该方法首先调用clear()清空二叉树。
     * 然后要从输入流(标准/文件流)按层次顺序输入在建二叉树各结点的值，依此建立一棵二叉树\n
     * 输入flag表示"空结点"
     * @warning 本方法可能调用ifstream类从istream类继承的的sync()方法，which可能导致未定义行为。
     * @note 要求对value_type类型重载了operator>>和operator<<
     */
    void createTree(const value_type &flag = value_type{}, std::istream &in = std::cin);

    /**
     * @brief 返回数据为x的结点的parent结点
     * 
     * @param x 目标结点的数据
     * @param flag parent不存在时返回的特殊标记
     * @return value_type parent结点的数据
     * 
     * @bug 二叉链表不允许访问结点的parent，本函数恒返回flag
     */
    value_type parent(value_type x, const value_type &flag) const { return flag; }

    /**
     * @brief 返回二叉树的高度(递归版本)
     * @details The height of n_i is the length of the longest path from n_i to a 
     * leaf. Thus all leaves are at height 0. \n
     * The height of a tree is equal to the height of the root.
     * 
     * @return size_type 二叉树的高度
     */
    size_type height() const;

    /**
     * @brief 返回二叉树的高度(非递归版本)
     * @details The height of n_i is the length of the longest path from n_i to a 
     * leaf. Thus all leaves are at height 0. \n
     * The height of a tree is equal to the height of the root.
     * 
     * @return size_type 二叉树的高度
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type height_loop() const;

    /**
     * @brief 返回二叉树的结点数(递归版本)
     * 
     * @return size_type 二叉树的结点数
     */
    size_type size() const;

    /**
     * @brief 返回二叉树的结点数(非递归版本)
     * 
     * @return size_type 二叉树的结点数
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type size_loop() const;

    /**
     * @brief 交换左右子树
     * 
     * @param _root 指向树的根结点的指针
     * @warning 不允许用户指定参数
     */
    void swaplr() { swaplr(root_); }

    /**
     * @brief 统计树中度为2的结点的个数
     */
    size_type CountDegreeTwo() const { return CountDegreeTwo(root_); }

    /**
     * @brief 返回是否完全二叉树
     * 
     * @return true 是完全二叉树
     * @return false 不是完全二叉树
     */
    bool isCompleteTree() const;

    /**
     * @brief 是否满二叉树
     * 
     * @note 定义满二叉树：任意一层的结点数都达到了最大值。
     * 
     * @return true 是满二叉树
     * @return false 非满二叉树
     */
    bool isFullBinaryTree() const;

    /**
     * @brief 判断两棵二叉树是否互为镜像
     * 两棵二叉树#1和#2互为镜像，如果二者皆为空树；或二者根结点的值相同，且#1的左、右子树与#2的右、左子树互为镜像
     * @param lhs 二叉树#1
     * @param rhs 二叉树#2
     * @return true #1 symmetrical to #2
     * @return false otherwise
     */
    static bool is_symmetrical_tree(const binaryTree &lhs, const binaryTree &rhs) { return is_symmetrical_subtree(lhs.root_, rhs.root_); }

    // 基类要求实现下列API
    /*
    virtual value_type root(value_type flag) const;
    virtual value_type parent(value_type x, value_type flag) const;
    virtual value_type lchild(value_type x, value_type flag) const;
    virtual value_type rchild(value_type x, value_type flag) const;
    virtual void delLeft(value_type x);
    virtual void delRight(value_type x);
    */

private:
    /**
     * @brief 在以root为根的树中(前序)查找数据为x的结点，返回指向该结点的指针
     * 
     * @param x 目标数据
     * @param root 目标二叉树的根结点的地址
     * @return BinNode* 指向查找到的数据为x的结点的指针。返回nullptr表示找不到。
     * 
     * @note 类的工具函数
     * @warning 树中有data相同的结点时，该方法只能找到前序序列中首次出现该数据的那个结点！
     */
    BinNode *find(const value_type &x, BinNode *root) const;

    /**
     * @brief 清空以root为根结点的树，包括清除根结点
     * 
     * @param root 指向目标树的根结点的指针
     * @note 类的工具函数
     * 
     * @details 函数执行完毕后，root将被置为nullptr
     */
    void clear(BinNode *&root);

    /**
     * @brief Internal method to clone subtree
     * 
     * @param _root 指向源二叉树的根结点的指针
     * @return BinNode* 指向新二叉树的根结点的指针
     */
    BinNode *clone(BinNode *_root) const;

    /**
     * @brief Internal method to 判断两棵二叉树是否相互对称
     * 
     * @param root1 指向二叉树#1的根结点的指针
     * @param root2 指向二叉树#2的根结点的指针
     * @return true #1和#2相互对称
     * @return false otherwise
     */
    static bool is_symmetrical_subtree(BinNode *root1, BinNode *root2);

    /**
     * @brief 前序遍历以root为根结点的树(递归版本)
     * 
     * @param root 指向目标树的根结点的指针
     * @param out 输出流对象，可以是标准输出流或文件流等
     * @note 类的工具函数
     */
    void
    preOrder(BinNode *root, std::ostream &out = std::cout) const;

    /**
     * @brief 中序遍历以root为根结点的树(递归版本)
     * 
     * @param root 指向目标树的根结点的指针
     * @param out 输出流对象，可以是标准输出流或文件流等
     * @note 类的工具函数
     */
    void inOrder(BinNode *root, std::ostream &out = std::cout) const;

    /**
     * @brief 后序遍历以root为根结点的树(递归版本)
     * 
     * @param root 指向目标树的根结点的指针
     * @param out 输出流对象，可以是标准输出流或文件流等
     * @note 类的工具函数
     */
    void postOrder(BinNode *root, std::ostream &out = std::cout) const;

    /* constexpr */ static Comparator is_less_than_ /* = Comparator{} */; ///< 比较器(function object)

    /**
     * @brief 比较value_type类型对象的大小。
     * 
     * @param lhs 左运算数
     * @param rhs 右运算数
     * @return true lhs < rhs
     * @return false lhs >= rhs
     */
    static bool value_type_less(const value_type &lhs, const value_type &rhs) { return is_less_than_(lhs, rhs); }

    /**
     * @brief 比较value_type类型对象的大小。
     * 
     * @param lhs 左运算数
     * @param rhs 右运算数
     * @return true lhs == rhs
     * @return false lhs != rhs
     */
    static bool value_type_equal(const value_type &lhs, const value_type &rhs) { return !is_less_than_(lhs, rhs) && !is_less_than_(rhs, lhs); }

    /**
     * @brief 比较value_type类型对象的大小。
     * 
     * @param lhs 左运算数
     * @param rhs 右运算数
     * @return true lhs <= rhs
     * @return false lhs > rhs
     */
    static bool value_type_less_equal(const value_type &lhs, const value_type &rhs) { return value_type_less(lhs, rhs) || value_type_equal(lhs, rhs); }

    /**
     * @brief 返回以指定结点为根结点的二叉树的规模(递归版本)
     * 
     * @param _root 指向根结点的指针
     * @return value_type 以指定结点为根结点的二叉树的规模
     * @note 类的工具函数
     */
    size_type size(BinNode *_root) const;

    /**
     * @brief 返回以指定结点为根结点的二叉树的规模(非递归版本)
     * 
     * @param _root 指向根结点的指针
     * @return value_type 以指定结点为根结点的二叉树的规模
     * @note 类的工具函数
     * @section Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type size_loop(BinNode *_root) const;

    /**
     * @brief 返回以指定结点为根结点的二叉树的高度(递归版本)
     * 
     * @param _root 指向根结点的指针
     * @return value_type 以指定结点为根结点的二叉树的高度
     * @note 类的工具函数
     */
    size_type height(BinNode *_root) const;

    /**
     * @brief 返回以指定结点为根结点的二叉树的高度(非递归版本)
     * 
     * @param _root 指向根结点的指针
     * @return value_type 以指定结点为根结点的二叉树的高度
     * @note 类的工具函数
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type height_loop(BinNode *_root) const;

    /**
     * @brief 统计树中度为2的结点的个数
     * 
     * @param _root 指向树的根结点的指针
     * @note 类的工具函数
     */
    size_type CountDegreeTwo(BinNode *_root) const;

    /**
     * @brief 交换左右子树
     * 
     * @param _root 指向树的根结点的指针
     * @note 类的工具函数
     */
    void swaplr(BinNode *_root);

    /**
     * @brief 判断两棵二叉树是否相同
     * "相同"是指：两棵树的形状及对应结点的值相等
     * @param _root1 指向二叉树#1的根结点的指针
     * @param _root2 指向二叉树#2的根结点的指针
     * @return true  两棵树相同
     * @return false 两棵树不相同
     */
    static bool is_equal_subtree(BinNode *_root1, BinNode *_root2);
};

template <class T, typename Comparator>
Comparator binaryTree<T, Comparator>::is_less_than_ = Comparator{};

template <class T, typename Comparator>
bool binaryTree<T, Comparator>::empty() const
{
    return !root_;
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::value_type binaryTree<T, Comparator>::root(const value_type &flag) const
{
    if (root_)
        return root_->data;

    return flag;
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::clear(BinNode *&root)
{
    if (!root)
        return;

    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::clear()
{
    clear(root_);
}

template <class T, typename Comparator>
binaryTree<T, Comparator>::~binaryTree()
{
    clear(root_);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::BinNode *binaryTree<T, Comparator>::clone(BinNode *_root) const
{
    if (!_root)
        return nullptr;
    return new BinNode(_root->data, clone(_root->left), clone(_root->right));
}

template <class T, class U>
bool binaryTree<T, U>::is_symmetrical_subtree(BinNode *_root1, BinNode *_root2)
{
    // 两棵空树
    if (!_root1 && !_root2)
        return true;
    // 一棵空树
    if (!_root1 || !_root2)
        return false;
    // 根结点不同
    if (!value_type_equal(_root1->data, _root2->data))
        return false;
    // 至此，#1和#2对称 iff. #1的左/右子树与#2的右/左子树对称
    return is_symmetrical_subtree(_root1->left, _root2->right) && is_symmetrical_subtree(_root2->left, _root1->right);
}

template <class T, class U>
bool binaryTree<T, U>::is_equal_subtree(BinNode *_root1, BinNode *_root2)
{
    // 两棵空树
    if (!_root1 && !_root2)
        return true;
    // 仅一棵为空
    if (!_root1 || !_root2)
        return false;
    // 根结点不同
    if (!value_type_equal(_root1->data, _root2->data))
        return false;
    return is_equal_subtree(_root1->left, _root2->left) && is_equal_subtree(_root1->right, _root2->right);
}

template <typename T, typename U>
bool binaryTree<T, U>::isFullBinaryTree() const
{
    size_type size_of_tree = size_loop();     // 二叉树的结点数
    size_type height_of_tree = height_loop(); // 二叉树的高度(0, 1, ...)
    // 因高度从0起，是满二叉树iff.有2^(height+1) - 1个结点
    // 这样使得空二叉树不是满二叉树
    if (((size_type(1) << (height_of_tree + 1)) - 1) == size_of_tree)
        return true;
    return false;
}

template <class T, typename Comparator>
bool binaryTree<T, Comparator>::isCompleteTree() const
{
    // 认为空树是完全二叉树
    if (!root_)
        return true;

    BinNode *current_node = nullptr;         // 当前结点
    Queue::seqQueue<BinNode *> node_queue{}; // 暂存结点的队列，用于层次遍历
    node_queue.push(root_);
    while (!node_queue.empty())
    {
        current_node = node_queue.front();
        node_queue.pop();
        // 若当前结点无左孩子但有右孩子，则非完全二叉树
        if (!current_node->left && current_node->right)
            return false;
        // 非空孩子入队
        if (current_node->left)
            node_queue.push(current_node->left);
        if (current_node->right)
            node_queue.push(current_node->right);
        /**
         * 至此，当前结点处理完毕。
         * 若当前结点有空孩子，则它是层序上的首个度非2结点。
         * 从而是完全二叉树iff.其后(不含)的结点全为叶子结点。
         * 
         * 函数只可能在此if中返回
         */
        if (!current_node->left || !current_node->right)
        {
            // 检查后续结点是否都是叶子结点
            while (!node_queue.empty())
            {
                current_node = node_queue.front();
                node_queue.pop();
                // 出现非叶子结点，判定为非完全二叉树
                if (current_node->left || current_node->right)
                    return false;
            }
            return true;
        }
    } // while (!node_queue.empty())
    // 控制不应到达此处
    throw(TreeException("Bug in member function \"isCompleteTree\", since control should not reach here", "isCompleteTree()"));
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::preOrder(BinNode *_root, std::ostream &out) const
{
    if (!_root)
        return;

    out << _root->data << ' ';
    preOrder(_root->left, out);
    preOrder(_root->right, out);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::preOrder_loop(/* BinNode *root, */ std::ostream &out) const
{
    // (First rule)
    /**
     * 引用类型的形参不需要记录。
     * 只需记录BinNode* _root。
     * 首次调用时，实参就是对象的根结点root_；
     * 该细节应被封装，故提供给用户的函数形参表不设_root。
     * 递归版本是有限次tail recursion，不必记录stage。
     */
    typedef BinNode *SnapShotStruct;

    // (Second rule)
    // 没有返回值，此步骤省略
    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack;

    // (Fourth rule)
    /**
     * 首次调用时，实参就是对象的根结点root_；
     * 该细节应被封装，故提供给用户的函数形参表不设_root。
     */
    SnapShotStruct currentSnapshot{root_};
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        // tail recursion，只需一个stage，此步省略

        // (Seventh rule)
        if (!currentSnapshot)
        {
            // (Eighth rule)
            // 无返回值，此步骤省略
            // (Ninth rule)
            continue;
        }
        out << currentSnapshot->data << ' ';

        // (Tenth rule)
        /**
         * 函数体内的递归调用返回后，唯一的行为是新的递归调用，
         * 故不必保存断点(分stage)，直接将所有tail recursions按反序进栈即可。
         * 注意到若某次递归调用的实参为0将导致空操作，所以若为空则不必进栈
         * (导致两次访问，可选)。
         */
        if (currentSnapshot->right)
            snapshotStack.push(currentSnapshot->right);
        if (currentSnapshot->left)
            snapshotStack.push(currentSnapshot->left);

        // (Ninth rule)
        continue;
    } // while (!snapshotStack.empty())
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::preOrder(std::ostream &out) const
{
    preOrder(root_, out);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::inOrder(BinNode *root, std::ostream &out) const
{
    if (!root)
        return;

    inOrder(root->left, out);
    out << root->data << ' ';
    inOrder(root->right, out);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::inOrder_loop(/* BinNode *root, */ std::ostream &out) const
{
    // (First rule)
    struct SnapShotStruct
    {
        BinNode *root;
        int stage;
    };

    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack;

    // (Fourth rule)
    SnapShotStruct currentSnapshot{root_, 0};
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        switch (currentSnapshot.stage)
        {
        case 0:
        {
            // (Seventh rule)
            if (!currentSnapshot.root)
            {
                // (Ninth rule)
                continue;
            }
            // (Tenth rule)
            currentSnapshot.stage = 1;
            snapshotStack.push(currentSnapshot);
            snapshotStack.push(SnapShotStruct{currentSnapshot.root->left, 0});
            break;
        }
        case 1:
        {
            // (Seventh rule)
            out << currentSnapshot.root->data << ' ';
            snapshotStack.push(SnapShotStruct{currentSnapshot.root->right, 0});
            // (Ninth rule)
            continue;
            break;
        }
        default:
        {
            assert(false);
        }
        } // switch (currentSnapshot.stage)

    } /* while (!snapshotStack.empty()) */
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::inOrder(std::ostream &out) const
{
    inOrder(root_, out);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::postOrder(BinNode *root, std::ostream &out) const
{
    if (!root)
        return;

    postOrder(root->left, out);
    postOrder(root->right, out);
    out << root->data << ' ';
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::postOrder_loop(/* BinNode *root, */ std::ostream &out) const
{
    // (First rule)
    struct SnapShotStruct
    {
        BinNode *root;
        int stage;
    };

    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack;

    // (Fourth rule)
    SnapShotStruct currentSnapshot{root_, 0};
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        switch (currentSnapshot.stage)
        {
        case 0:
        {
            // (Seventh rule)
            if (!currentSnapshot.root)
            {
                // (Ninth rule)
                continue;
            }
            // (Tenth rule)
            currentSnapshot.stage = 1;
            snapshotStack.push(currentSnapshot);
            /**
             * 连续递归调用，归入一个stage，直接反序进栈即可
             */
            snapshotStack.push(SnapShotStruct{currentSnapshot.root->right, 0});
            snapshotStack.push(SnapShotStruct{currentSnapshot.root->left, 0});
            break;
        }
        case 1:
        {
            // (Seventh rule)
            out << currentSnapshot.root->data << ' ';
            // (Ninth rule)
            continue;
            break;
        }
        default:
        {
            assert(false);
        }
        } // switch (currentSnapshot.stage)

    } /* while (!snapshotStack.empty()) */
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::postOrder(std::ostream &out) const
{
    postOrder(root_, out);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::levelOrder(std::ostream &out) const
{
    if (!root_)
        return;

    BinNode *current_node = nullptr;
    Queue::seqQueue<BinNode *> node_queue{};
    node_queue.push(root_);

    while (!node_queue.empty())
    {
        current_node = node_queue.front();
        node_queue.pop();

        if (current_node->left)
            node_queue.push(current_node->left);

        if (current_node->right)
            node_queue.push(current_node->right);

        out << current_node->data << ' ';
    }
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::BinNode *binaryTree<T, Comparator>::find(const value_type &x, BinNode *root) const
{
    if (!root)
        return nullptr;

    if (value_type_equal(root->data, x))
        return root;

    BinNode *target = nullptr;
    if ((target = find(x, root->left)))
        return target;

    return find(x, root->right);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::delLeft(const value_type &x)
{
    BinNode *target = find(x, root_);
    if (!target)
        return;

    clear(target->left);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::delRight(const value_type &x)
{
    BinNode *target = find(x, root_);
    if (!target)
        return;

    clear(target->right);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::value_type binaryTree<T, Comparator>::lchild(const value_type &x, const value_type &flag) const
{
    BinNode *target = find(x, root_);
    if (!target || !target->left)
        return flag;

    return target->left->data;
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::value_type binaryTree<T, Comparator>::rchild(const value_type &x, const value_type &flag) const
{
    BinNode *target = find(x, root_);
    if (!target || !target->right)
        return flag;

    return target->right->data;
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::swaplr(BinNode *_root)
{
    if (!_root)
        return;

    swaplr(_root->left);
    swaplr(_root->right);
    std::swap(_root->left, _root->right);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::CountDegreeTwo(BinNode *_root) const
{
    // 若为空树，或无叶子结点，则返回0
    if (!_root || (!_root->left && !_root->right))
        return 0;

    return static_cast<size_type>(_root->left && _root->right) + CountDegreeTwo(_root->left) + CountDegreeTwo(_root->right);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type
binaryTree<T, Comparator>::height(BinNode *_root) const
{
    if (!_root || (!_root->left && !_root->right)) // warning: suggest parentheses around '&&' within '||' [-Wparentheses]
        return 0;

    size_type left_height = height(_root->left);
    size_type right_height = height(_root->right);
    return 1 + ((left_height > right_height) ? left_height : right_height);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::height_loop(BinNode *__root) const
{
    // (First rule)
    struct SnapShotStruct // this can be declared as local structure since it will be only used within this function.
    {
        // 不要初始化struct的成员！否则无法使用初始化列表，除非定义构造函数
        BinNode *_root;         // parameter that changes
        size_type left_height;  // the local variable that changes
        size_type right_height; // the local variable that changes
        int stage;              // the stage variable to track where the snapshot has taken
    };

    // (Second rule)
    size_type returnVal; // the return value at the point

    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack{};

    // (Fourth rule)
    SnapShotStruct currentSnapshot{__root, 0, 0, 0}; // as initial stage
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        switch (currentSnapshot.stage)
        {
            // (Seventh rule)
        case 0:
        {
            if (!currentSnapshot._root || (!currentSnapshot._root->left && !currentSnapshot._root->right))
            {
                // (Eighth rule && Ninth rule)
                returnVal = 0;
                continue;
            }

            // (Tenth rule)
            currentSnapshot.stage = 1; // current snapshot is done processing and only waiting for result of calling itself, so becomes stage "1"
            snapshotStack.push(currentSnapshot);

            // Create a new snapshot for calling itself
            SnapShotStruct newSnapshot{currentSnapshot._root->left, 0, 0, 0}; // give parameter as parameter given when calling itself (first case height(_root->left)). Since it will start from the beginning of the function, give the initial stage
            snapshotStack.push(newSnapshot);
            continue;

            break;
        }
            // (Seventh rule)
        case 1:
        {
            // (Tenth rule)
            currentSnapshot.left_height = returnVal;
            currentSnapshot.stage = 2;
            snapshotStack.push(currentSnapshot);

            // Create a new snapshot for calling itself
            SnapShotStruct newSnapshot{currentSnapshot._root->right, 0, 0, 0}; // give parameter as parameter given when calling itself (first case height(_root->right)). Since it will start from the beginning of the function, give the initial stage
            snapshotStack.push(newSnapshot);
            continue;

            break;
        }
        case 2:
        {
            // (Seventh rule)
            currentSnapshot.right_height = returnVal;

            // (Eighth rule)
            returnVal = 1 + ((currentSnapshot.left_height > currentSnapshot.right_height) ? currentSnapshot.left_height : currentSnapshot.right_height);

            // (Ninth rule)
            continue;
        }
        default:
        {
            assert(false);
        }
        } // switch (currentSnapshot.stage)

    } // while (!snapshotStack.empty())

    // (Second rule)
    return returnVal;
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::height() const
{
    return height(root_);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::height_loop() const
{
    return height_loop(root_);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::size(BinNode *_root) const
{
    if (!_root)
        return 0;

    // think this as
    // size_type addVal = size(_root->left);
    // addVal = 1 + addVal + size(_root->right);
    // return addVal;
    return 1 + size(_root->left) + size(_root->right);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::size_loop(BinNode *__root) const
{
    // (First rule)
    struct SnapShotStruct
    {
        // 不要初始化struct的成员！否则无法使用初始化列表，除非定义构造函数
        BinNode *_root;   // - parameter input
        size_type addVal; // - local variable that will be used after returning from the function call
        int stage;        // - Since there is process needed to be done after recursive call. (Sixth rule)
    };

    // (Second rule)
    size_type returnVal{0}; // This value will represent the role of the return function in the recursive function.

    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack{};

    // (Fourth rule)
    SnapShotStruct currentSnapshot{__root, 0, 0};
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        switch (currentSnapshot.stage)
        {
        case 0:
        {
            // (Seventh rule)
            if (!currentSnapshot._root)
            {
                // (Eighth rule)
                returnVal = 0;

                // (Ninth rule)
                continue;
            }

            // (Tenth rule)
            currentSnapshot.stage = 1;           // - current snapshot need to process after returning from the recursive call
            snapshotStack.push(currentSnapshot); // - this MUST pushed into stack before new snapshot!

            // Create a new snapshot for calling itself ( size(_root->left); )
            SnapShotStruct newSnapshot{currentSnapshot._root->left, 0, 0}; // - give parameter as parameter given when calling itself. Since it will start from the beginning of the function, give the initial stage.
            snapshotStack.push(newSnapshot);

            continue;
            break;
        }
        case 1:
        {
            // (Seventh rule)
            currentSnapshot.addVal = returnVal;

            // (Tenth rule)
            currentSnapshot.stage = 2;
            snapshotStack.push(currentSnapshot);

            // Create a new snapshot for calling itself ( size(_root->right); )
            SnapShotStruct newSnapshot{currentSnapshot._root->right, 0, 0}; // - give parameter as parameter given when calling itself. Since it will start from the beginning of the function, give the initial stage.
            snapshotStack.push(newSnapshot);

            continue;
            break;
        }
        case 2:
        {
            // (Seventh rule)
            // (Eighth rule)
            returnVal = 1 + currentSnapshot.addVal + returnVal;

            //  (Ninth rule)
            continue;
            break;
        }
        default:
        {
            assert(false);
        }
        } // switch (currentSnapshot.stage)

    } // while (!snapshotStack.empty())

    // (Second rule)
    return returnVal;
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::size() const
{
    return size(root_);
}

template <class T, typename Comparator>
typename binaryTree<T, Comparator>::size_type binaryTree<T, Comparator>::size_loop() const
{
    return size_loop(root_);
}

template <class T, typename Comparator>
void binaryTree<T, Comparator>::createTree(const value_type &flag, std::istream &in)
{
    clear();

    BinNode *this_node{};                     // 正在处理的结点
    value_type this_data = flag;              // 暂存数据
    Queue::linkQueue<BinNode *> node_queue{}; // 存放待处理(data已定而child待定)结点的队列

    // 要求从终端输入一个合法数据，作为根结点的data
    do
    {
        std::cout << "\n请输入根结点: ";
        in >> this_data;

        // 若为非法输入，或输入了代表空结点的特殊标记flag，则要求重新输入
        if (std::cin.fail() || value_type_equal(this_data, flag))
        {
            in.clear();
            in.sync();
            std::cerr << "根结点必须含合法数据！\n";
            continue;
        }
        break;
    } while (true);

    root_ = new BinNode(this_data, 0, 0);
    node_queue.push(root_);

    while (!node_queue.empty())
    {
        // 取当前结点
        this_node = node_queue.front();
        node_queue.pop();

        // 从终端请求当前结点的左child。若有左child，则将左child进node_queue表示待处理。
        this_data = flag; // 初始化数据暂存器
        do
        {
            std::cout << "\n请输入结点：" << this_node->data << " 的left child（输入 " << flag << " 表示无）：\n";
            in >> this_data;

            // 若为非法输入，要求重新输入
            if (in.fail())
            {
                in.clear();
                in.sync(); // 读文件流sync()行为未定义？
                std::cerr << "非法输入！";
                continue;
            }

            // 若指定当前结点无左child
            if (value_type_equal(this_data, flag))
            {
                in.sync(); // 读文件流sync()行为未定义？
                std::cout << "已指定该结点无left child\n";
                break;
            }

            // 当前结点有左child，则将左child连到parent上，然后将左child入队列（表示左child的children待定）
            std::cout << "已指定左child为：" << this_data << '\n';
            node_queue.push(this_node->left = new BinNode(this_data, 0, 0));

            break;
        } while (true);

        // 从终端请求当前结点的右child。若有右child，则将右child进node_queue表示待处理。
        this_data = flag; // 初始化数据暂存器
        do
        {
            std::cout << "\n请输入结点：" << this_node->data << " 的right child（输入 " << flag << " 表示无）：\n";
            in >> this_data;

            // 若为非法输入，要求重新输入
            if (in.fail())
            {
                in.clear();
                in.sync(); // 读文件流sync()行为未定义？
                std::cerr << "非法输入！";
                continue;
            }

            // 若指定当前结点无右child
            if (value_type_equal(this_data, flag))
            {
                in.sync(); // 读文件流sync()行为未定义？
                std::cout << "已指定该结点无right child\n";
                break;
            }

            // 当前结点有右child，则将左child连到parent上，然后将右child入队列（表示右child的children待定）
            std::cout << "已指定右child为：" << this_data << '\n';
            node_queue.push(this_node->right = new BinNode(this_data, 0, 0));

            break;
        } while (true);

        /* 当前结点处理完毕，准备处理node_queue中的下个结点 */

    } // while (!node_queue.empty())
}

template <class T, typename Comparator>
void printBinaryTree(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out)
{
    if (bin_tree.empty())
    {
        out << "是一棵空二叉树\n";
        return;
    }

    out << "(层次打印) 格式：\"parent    lchild    rchild\" ( " << flag << " 表示空结点 )\n";
    Queue::seqQueue<typename binaryTree<T, Comparator>::value_type> node_data_queue{}; // 存放待打印结点的队列
    /*typename*/ typename binaryTree<T, Comparator>::value_type this_data = flag;      // 暂存当前结点的data
    typename binaryTree<T, Comparator>::value_type left_data = flag;                   // 暂存左child的data
    typename binaryTree<T, Comparator>::value_type right_data = flag;                  // 暂存右child的data

    // 根结点的data入队
    node_data_queue.push(bin_tree.root(flag));

    while (!node_data_queue.empty())
    {
        // 取当前结点的data
        this_data = node_data_queue.front();
        node_data_queue.pop();

        // 找以当前data为data的结点的左、右child的data，并打印到标准输出设备
        out << this_data << '\t' << (left_data = bin_tree.lchild(this_data, flag)) << '\t' << (right_data = bin_tree.rchild(this_data, flag)) << '\n';

        // 若以当前data为data的结点有children，则将children入队，表示待打印
        if (!bin_tree.value_type_equal(left_data, flag))
            node_data_queue.push(left_data);

        if (!bin_tree.value_type_equal(right_data, flag))
            node_data_queue.push(right_data);
    }
}

template <class T, typename Comparator>
bool operator==(const binaryTree<T, Comparator> &lhs, const binaryTree<T, Comparator> &rhs)
{
    return binaryTree<T, Comparator>::is_equal_subtree(lhs.root_, rhs.root_);
}

} // namespace Tree

#endif /* INCLUDE_BINARYTREE_HH_ */
