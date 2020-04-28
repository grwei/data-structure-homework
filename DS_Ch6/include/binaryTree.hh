/****************************************************
 * @file binaryTree.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief �������Ķ�������ʵ��
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
 * @brief �ö�������ʵ�ֵĶ�������
 * 
 * @tparam T ��������
 * @tparam Comparator �������͵ıȽ����࣬Ĭ��Ϊstd::less<T> 
 * 
 * @details ������T������operator<����Comparator��Ĭ������std::less<T>������operator<����ʵ����ʱ����ָ��tparam2��\n
 * ����Ҫ��ָ��ģ�����Comparator��which is a function object, ������bool operator(T t1, T t2)����������t1 < t2ʱ����true��
 * @details Ҫ���T������operator<< �� operator>>������ÿ������������һ������
 * @warning �����д洢��data��ͬ�Ľ�㣬��˽��find�������ø÷����Ĺ��з������ܳ����쳣��
 */
template <typename T, typename Comparator = std::less<T>>
class binaryTree;

/**
 * @brief ���һ�ö�����
 * 
 * @tparam T ����������������
 * @param bin_tree ��������Ķ���
 * @param flag ���ڱ�ʾ�ս���������
 * @param out ���������Ĭ����std::cout��Ҳ������ostream�༰��������Ķ��󣬰�������ļ����ȡ�
 * 
 * @details �����˳�����ÿ����㼰��children�����ڲ��Զ�������ʵ�ֵ���ȷ�ԡ�
 * �ú����ٶ�����û��data��ͬ�Ľ��
 * @note �ú���ģ�屻����ΪbinaryTree<T>�����Ԫ���������ã�ʵ���ϲ�������Ԫ��\n
 * ���ڲ��ԣ�
 * -# ��������ʵ�ֵ���ȷ�ԣ�����lchild��rchild��root��API
 * -# ģ����ͬ��ģ�����Ԫ
 * -# ģ�庯����ģ��ʵ�ε��ƶϣ�tparam2�Ƿ�����binaryTree��tparam2��Ĭ��ֵ�ƶϣ�
 * @deprecated �ú������������ã�������ʽ�汾��ɾ����
 * @bug bin_tree�в�������data��ͬ�Ľ�㣬������ܵ�������ѭ����
 */
template <class T, typename Comparator>
void printBinaryTree(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout);

/**
 * @brief �Ƚ����ö������Ƿ���ͬ
 * "��ͬ"��ָ��
 * @tparam T ��������
 * @tparam Comparator �������͵ıȽ����࣬Ĭ��Ϊstd::less<T>
 * @note �˺���ģ���ģ��ʵ���ɺ���ʵ�α��ƶϣ��û�����ָ��
 * @details ������T������operator<����Comparator��Ĭ������std::less<T>������operator<����ʵ����ʱ����ָ��tparam2��\n
 * ����Ҫ��ָ��ģ�����Comparator��which is a function object, ������bool operator(T t1, T t2)����������t1 < t2ʱ����true��
 * @param lhs ������#1
 * @param rhs ������#2
 * @return true #1��#2��ͬ
 * @return false #1��#2��ͬ
 */
template <class T, typename Comparator>
bool operator==(const binaryTree<T, Comparator> &lhs, const binaryTree<T, Comparator> &rhs);

template <typename T, typename Comparator>
class binaryTree /* : binTree<T> */
{
    /**
     * �����ڴ�����������Ԫ(invalid use of incomplete type)��
     * ԭ������ڲ�����value_typeδ������
     * ֻ�����Ԫ��������typedef�󼴿�
     */
    // friend void printBinaryTree</*T, Comparator*/>(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out);
    friend bool operator==</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &lhs, const binaryTree /*<T, Comparator>*/ &rhs);

public:
    /**
     * @brief ���ͱ�������
     * 
     */
    typedef T value_type;                      ///< ��������
    typedef value_type &reference;             ///< ���ݵ�����
    typedef const value_type &const_reference; ///< ���ݵĳ�������
    typedef size_t size_type;                  ///< ����������

    friend void printBinaryTree</*T, Comparator*/>(const binaryTree /*<T, Comparator>*/ &bin_tree, const typename binaryTree /*<T, Comparator>*/ ::value_type &flag, std::ostream &out);

private:
    /**
     * @brief ��������Ľ����
     * 
     */
    struct BinNode
    {
        value_type data; ///< ����
        BinNode *left;   ///< ָ����child
        BinNode *right;  ///< ָ����child

        /**
         * @brief Construct a new Bin Node object
         * 
         * @param _data ����
         * @param _left ��child�ĵ�ַ
         * @param _right ��child�ĵ�ַ
         */
        explicit BinNode(const value_type &_data = value_type{}, BinNode *_left = nullptr, BinNode *_right = nullptr) : data(_data), left(_left), right(_right) {}

        /**
         * @brief Construct a new Bin Node object
         * 
         * @param _data ����
         * @param _left ��child�ĵ�ַ
         * @param _right ��child�ĵ�ַ
         */
        explicit BinNode(value_type &&_data, BinNode *_left, BinNode *_right) : data(std::move(_data)), left(_left), right(_right) {}

        /**
         * @brief Destroy the Bin Node object
         * 
         */
        ~BinNode() = default;
    };

    BinNode *root_; ///< �������ĸ����

public:
    /**
     * @brief Construct a new binary Tree object
     * 
     * ����һ�ÿ���
     * 
     */
    binaryTree() : root_(nullptr){};

    /**
     * @brief Construct a new binary Tree object
     * 
     * ����һ�ô��и��ڵ����
     * 
     * @param x ����������
     */
    explicit binaryTree(const value_type &x) : root_(new BinNode(x)) {}

    /**
     * @brief Construct a new binary Tree object
     * �������캯��
     * @param rhs Դ����
     * @note �ο�C++���ģʽ����ԭ��ģʽ
     */
    binaryTree(const binaryTree &rhs) : binaryTree() { root_ = clone(rhs.root_); }

    /**
     * @brief ��ֵ���������
     * 
     * @param rhs Դ����
     * @return binaryTree& Ŀ�Ķ��������
     */
    binaryTree &operator=(const binaryTree &rhs)
    {
        // ����ģʽ������������ֵ���������
        binaryTree copy = rhs;  // Ҫ���ø��ƹ��캯��
        std::swap(*this, copy); // Ҫ�����ƶ����졢�ƶ���ֵ����
        return *this;
    }

    /**
     * @brief Construct a new binary Tree object
     * �ƶ����캯��
     * @param rhs Դ������ֵ
     */
    binaryTree(binaryTree &&rhs) : root_{rhs.root_} { rhs.root_ = nullptr; }

    /**
     * @brief �ƶ���ֵ�����
     * 
     * @param rhs Դ������ֵ
     * @return binaryTree& Ŀ�Ķ��������
     */
    binaryTree &operator=(binaryTree &&rhs)
    {
        // ��ֹ����ֵ
        if (rhs.root_ == root_)
            return *this;
        std::swap(root_, rhs.root_); // ������ԭ���������ά������Դת���Ҳ��������Ӷ������ͷ�
        return *this;
    }

    /**
     * @brief Destroy the binary Tree object
     * 
     */
    ~binaryTree();

    /**
     * @brief ��ն�����
     * �������غ󣬶���ĳ�Աroot_������nullptr
     */
    void clear();

    /**
     * @brief �ж϶������Ƿ�Ϊ����
     * 
     * @return true �ǿ���
     * @return false �ǿ���
     */
    bool empty() const;

    /**
     * @brief ���ظ���������
     * 
     * @param flag Ϊ����ʱ���ص�������
     * @return value_type ����������
     */
    value_type root(const value_type &flag) const;

    /**
     * @brief �������Ϊx�Ľ�����child
     * 
     * @param x Ŀ���������
     * @param flag ����childʱ���صı��
     * @return value_type ��child������
     * @warning ������data��ͬ�Ľ��ʱ���÷���ֻ�ܷ��ʵ�ǰ���������״γ��ָ����ݵ��Ǹ���㣡
     */
    value_type lchild(const value_type &x, const value_type &flag) const;

    /**
     * @brief �������Ϊx�Ľ�����child
     * 
     * @param x Ŀ���������
     * @param flag ����childʱ���صı��
     * @return value_type ��child������
     * @warning ������data��ͬ�Ľ��ʱ���÷���ֻ�ܷ��ʵ�ǰ���������״γ��ָ����ݵ��Ǹ���㣡
     */
    value_type rchild(const value_type &x, const value_type &flag) const;

    /**
     * @brief ɾ����subtree
     * 
     * @param x Ŀ���㡣�Ըý�����childΪ����������ɾ��
     * @warning ������data��ͬ�Ľ��ʱ���÷���ֻ�ܷ��ʵ�ǰ���������״γ��ָ����ݵ��Ǹ���㣡
     */
    void delLeft(const value_type &x);

    /**
     * @brief ɾ����subtree
     * 
     * @param x Ŀ���㡣�Ըýڵ����childΪ����������ɾ��
     * @warning ������data��ͬ�Ľ��ʱ���÷���ֻ�ܷ��ʵ�ǰ���������״γ��ָ����ݵ��Ǹ���㣡
     */
    void delRight(const value_type &x);

    /**
     * @brief ǰ�����(�ݹ�汾)
     * 
     * ǰ���ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void preOrder(std::ostream &out = std::cout) const;

    /**
     * @brief ǰ�����(�ǵݹ�汾)
     * 
     * ǰ���ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void preOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief �������(�ݹ�汾)
     * 
     * �����ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void inOrder(std::ostream &out = std::cout) const;

    /**
     * @brief �������(�ǵݹ�汾)
     * 
     * �����ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void inOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief �������(�ݹ�汾)
     * 
     * �����ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void postOrder(std::ostream &out = std::cout) const;

    /**
     * @brief �������(�ǵݹ�汾)
     * 
     * �����ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void postOrder_loop(/* BinNode *root, */ std::ostream &out = std::cout) const;

    /**
     * @brief ��α���
     * 
     * ��δ�ӡ���������������ݵ���׼����豸
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     */
    void levelOrder(std::ostream &out = std::cout) const;

    /**
     * @brief Create a Tree object
     * 
     * @param flag "�ս��"��������
     * @param in ���������󣬿�����cin, ����ifstream��Ķ����
     * 
     * @ details �÷������ȵ���clear()��ն�������
     * Ȼ��Ҫ��������(��׼/�ļ���)�����˳�������ڽ�������������ֵ�����˽���һ�ö�����\n
     * ����flag��ʾ"�ս��"
     * @warning ���������ܵ���ifstream���istream��̳еĵ�sync()������which���ܵ���δ������Ϊ��
     * @note Ҫ���value_type����������operator>>��operator<<
     */
    void createTree(const value_type &flag = value_type{}, std::istream &in = std::cin);

    /**
     * @brief ��������Ϊx�Ľ���parent���
     * 
     * @param x Ŀ���������
     * @param flag parent������ʱ���ص�������
     * @return value_type parent��������
     * 
     * @bug ��������������ʽ���parent���������㷵��flag
     */
    value_type parent(value_type x, const value_type &flag) const { return flag; }

    /**
     * @brief ���ض������ĸ߶�(�ݹ�汾)
     * @details The height of n_i is the length of the longest path from n_i to a 
     * leaf. Thus all leaves are at height 0. \n
     * The height of a tree is equal to the height of the root.
     * 
     * @return size_type �������ĸ߶�
     */
    size_type height() const;

    /**
     * @brief ���ض������ĸ߶�(�ǵݹ�汾)
     * @details The height of n_i is the length of the longest path from n_i to a 
     * leaf. Thus all leaves are at height 0. \n
     * The height of a tree is equal to the height of the root.
     * 
     * @return size_type �������ĸ߶�
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type height_loop() const;

    /**
     * @brief ���ض������Ľ����(�ݹ�汾)
     * 
     * @return size_type �������Ľ����
     */
    size_type size() const;

    /**
     * @brief ���ض������Ľ����(�ǵݹ�汾)
     * 
     * @return size_type �������Ľ����
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type size_loop() const;

    /**
     * @brief ������������
     * 
     * @param _root ָ�����ĸ�����ָ��
     * @warning �������û�ָ������
     */
    void swaplr() { swaplr(root_); }

    /**
     * @brief ͳ�����ж�Ϊ2�Ľ��ĸ���
     */
    size_type CountDegreeTwo() const { return CountDegreeTwo(root_); }

    /**
     * @brief �����Ƿ���ȫ������
     * 
     * @return true ����ȫ������
     * @return false ������ȫ������
     */
    bool isCompleteTree() const;

    /**
     * @brief �Ƿ���������
     * 
     * @note ������������������һ��Ľ�������ﵽ�����ֵ��
     * 
     * @return true ����������
     * @return false ����������
     */
    bool isFullBinaryTree() const;

    /**
     * @brief �ж����ö������Ƿ�Ϊ����
     * ���ö�����#1��#2��Ϊ����������߽�Ϊ����������߸�����ֵ��ͬ����#1������������#2���ҡ���������Ϊ����
     * @param lhs ������#1
     * @param rhs ������#2
     * @return true #1 symmetrical to #2
     * @return false otherwise
     */
    static bool is_symmetrical_tree(const binaryTree &lhs, const binaryTree &rhs) { return is_symmetrical_subtree(lhs.root_, rhs.root_); }

    // ����Ҫ��ʵ������API
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
     * @brief ����rootΪ��������(ǰ��)��������Ϊx�Ľ�㣬����ָ��ý���ָ��
     * 
     * @param x Ŀ������
     * @param root Ŀ��������ĸ����ĵ�ַ
     * @return BinNode* ָ����ҵ�������Ϊx�Ľ���ָ�롣����nullptr��ʾ�Ҳ�����
     * 
     * @note ��Ĺ��ߺ���
     * @warning ������data��ͬ�Ľ��ʱ���÷���ֻ���ҵ�ǰ���������״γ��ָ����ݵ��Ǹ���㣡
     */
    BinNode *find(const value_type &x, BinNode *root) const;

    /**
     * @brief �����rootΪ����������������������
     * 
     * @param root ָ��Ŀ�����ĸ�����ָ��
     * @note ��Ĺ��ߺ���
     * 
     * @details ����ִ����Ϻ�root������Ϊnullptr
     */
    void clear(BinNode *&root);

    /**
     * @brief Internal method to clone subtree
     * 
     * @param _root ָ��Դ�������ĸ�����ָ��
     * @return BinNode* ָ���¶������ĸ�����ָ��
     */
    BinNode *clone(BinNode *_root) const;

    /**
     * @brief Internal method to �ж����ö������Ƿ��໥�Գ�
     * 
     * @param root1 ָ�������#1�ĸ�����ָ��
     * @param root2 ָ�������#2�ĸ�����ָ��
     * @return true #1��#2�໥�Գ�
     * @return false otherwise
     */
    static bool is_symmetrical_subtree(BinNode *root1, BinNode *root2);

    /**
     * @brief ǰ�������rootΪ��������(�ݹ�汾)
     * 
     * @param root ָ��Ŀ�����ĸ�����ָ��
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     * @note ��Ĺ��ߺ���
     */
    void
    preOrder(BinNode *root, std::ostream &out = std::cout) const;

    /**
     * @brief ���������rootΪ��������(�ݹ�汾)
     * 
     * @param root ָ��Ŀ�����ĸ�����ָ��
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     * @note ��Ĺ��ߺ���
     */
    void inOrder(BinNode *root, std::ostream &out = std::cout) const;

    /**
     * @brief ���������rootΪ��������(�ݹ�汾)
     * 
     * @param root ָ��Ŀ�����ĸ�����ָ��
     * @param out ��������󣬿����Ǳ�׼��������ļ�����
     * @note ��Ĺ��ߺ���
     */
    void postOrder(BinNode *root, std::ostream &out = std::cout) const;

    /* constexpr */ static Comparator is_less_than_ /* = Comparator{} */; ///< �Ƚ���(function object)

    /**
     * @brief �Ƚ�value_type���Ͷ���Ĵ�С��
     * 
     * @param lhs ��������
     * @param rhs ��������
     * @return true lhs < rhs
     * @return false lhs >= rhs
     */
    static bool value_type_less(const value_type &lhs, const value_type &rhs) { return is_less_than_(lhs, rhs); }

    /**
     * @brief �Ƚ�value_type���Ͷ���Ĵ�С��
     * 
     * @param lhs ��������
     * @param rhs ��������
     * @return true lhs == rhs
     * @return false lhs != rhs
     */
    static bool value_type_equal(const value_type &lhs, const value_type &rhs) { return !is_less_than_(lhs, rhs) && !is_less_than_(rhs, lhs); }

    /**
     * @brief �Ƚ�value_type���Ͷ���Ĵ�С��
     * 
     * @param lhs ��������
     * @param rhs ��������
     * @return true lhs <= rhs
     * @return false lhs > rhs
     */
    static bool value_type_less_equal(const value_type &lhs, const value_type &rhs) { return value_type_less(lhs, rhs) || value_type_equal(lhs, rhs); }

    /**
     * @brief ������ָ�����Ϊ�����Ķ������Ĺ�ģ(�ݹ�汾)
     * 
     * @param _root ָ�������ָ��
     * @return value_type ��ָ�����Ϊ�����Ķ������Ĺ�ģ
     * @note ��Ĺ��ߺ���
     */
    size_type size(BinNode *_root) const;

    /**
     * @brief ������ָ�����Ϊ�����Ķ������Ĺ�ģ(�ǵݹ�汾)
     * 
     * @param _root ָ�������ָ��
     * @return value_type ��ָ�����Ϊ�����Ķ������Ĺ�ģ
     * @note ��Ĺ��ߺ���
     * @section Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type size_loop(BinNode *_root) const;

    /**
     * @brief ������ָ�����Ϊ�����Ķ������ĸ߶�(�ݹ�汾)
     * 
     * @param _root ָ�������ָ��
     * @return value_type ��ָ�����Ϊ�����Ķ������ĸ߶�
     * @note ��Ĺ��ߺ���
     */
    size_type height(BinNode *_root) const;

    /**
     * @brief ������ָ�����Ϊ�����Ķ������ĸ߶�(�ǵݹ�汾)
     * 
     * @param _root ָ�������ָ��
     * @return value_type ��ָ�����Ϊ�����Ķ������ĸ߶�
     * @note ��Ĺ��ߺ���
     * @note Reference
     * https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
     */
    size_type height_loop(BinNode *_root) const;

    /**
     * @brief ͳ�����ж�Ϊ2�Ľ��ĸ���
     * 
     * @param _root ָ�����ĸ�����ָ��
     * @note ��Ĺ��ߺ���
     */
    size_type CountDegreeTwo(BinNode *_root) const;

    /**
     * @brief ������������
     * 
     * @param _root ָ�����ĸ�����ָ��
     * @note ��Ĺ��ߺ���
     */
    void swaplr(BinNode *_root);

    /**
     * @brief �ж����ö������Ƿ���ͬ
     * "��ͬ"��ָ������������״����Ӧ����ֵ���
     * @param _root1 ָ�������#1�ĸ�����ָ��
     * @param _root2 ָ�������#2�ĸ�����ָ��
     * @return true  ��������ͬ
     * @return false ����������ͬ
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
    // ���ÿ���
    if (!_root1 && !_root2)
        return true;
    // һ�ÿ���
    if (!_root1 || !_root2)
        return false;
    // ����㲻ͬ
    if (!value_type_equal(_root1->data, _root2->data))
        return false;
    // ���ˣ�#1��#2�Գ� iff. #1����/��������#2����/�������Գ�
    return is_symmetrical_subtree(_root1->left, _root2->right) && is_symmetrical_subtree(_root2->left, _root1->right);
}

template <class T, class U>
bool binaryTree<T, U>::is_equal_subtree(BinNode *_root1, BinNode *_root2)
{
    // ���ÿ���
    if (!_root1 && !_root2)
        return true;
    // ��һ��Ϊ��
    if (!_root1 || !_root2)
        return false;
    // ����㲻ͬ
    if (!value_type_equal(_root1->data, _root2->data))
        return false;
    return is_equal_subtree(_root1->left, _root2->left) && is_equal_subtree(_root1->right, _root2->right);
}

template <typename T, typename U>
bool binaryTree<T, U>::isFullBinaryTree() const
{
    size_type size_of_tree = size_loop();     // �������Ľ����
    size_type height_of_tree = height_loop(); // �������ĸ߶�(0, 1, ...)
    // ��߶ȴ�0������������iff.��2^(height+1) - 1�����
    // ����ʹ�ÿն�����������������
    if (((size_type(1) << (height_of_tree + 1)) - 1) == size_of_tree)
        return true;
    return false;
}

template <class T, typename Comparator>
bool binaryTree<T, Comparator>::isCompleteTree() const
{
    // ��Ϊ��������ȫ������
    if (!root_)
        return true;

    BinNode *current_node = nullptr;         // ��ǰ���
    Queue::seqQueue<BinNode *> node_queue{}; // �ݴ���Ķ��У����ڲ�α���
    node_queue.push(root_);
    while (!node_queue.empty())
    {
        current_node = node_queue.front();
        node_queue.pop();
        // ����ǰ��������ӵ����Һ��ӣ������ȫ������
        if (!current_node->left && current_node->right)
            return false;
        // �ǿպ������
        if (current_node->left)
            node_queue.push(current_node->left);
        if (current_node->right)
            node_queue.push(current_node->right);
        /**
         * ���ˣ���ǰ��㴦����ϡ�
         * ����ǰ����пպ��ӣ������ǲ����ϵ��׸��ȷ�2��㡣
         * �Ӷ�����ȫ������iff.���(����)�Ľ��ȫΪҶ�ӽ�㡣
         * 
         * ����ֻ�����ڴ�if�з���
         */
        if (!current_node->left || !current_node->right)
        {
            // ����������Ƿ���Ҷ�ӽ��
            while (!node_queue.empty())
            {
                current_node = node_queue.front();
                node_queue.pop();
                // ���ַ�Ҷ�ӽ�㣬�ж�Ϊ����ȫ������
                if (current_node->left || current_node->right)
                    return false;
            }
            return true;
        }
    } // while (!node_queue.empty())
    // ���Ʋ�Ӧ����˴�
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
     * �������͵��ββ���Ҫ��¼��
     * ֻ���¼BinNode* _root��
     * �״ε���ʱ��ʵ�ξ��Ƕ���ĸ����root_��
     * ��ϸ��Ӧ����װ�����ṩ���û��ĺ����βα���_root��
     * �ݹ�汾�����޴�tail recursion�����ؼ�¼stage��
     */
    typedef BinNode *SnapShotStruct;

    // (Second rule)
    // û�з���ֵ���˲���ʡ��
    // (Third rule)
    Stack::seqStack<SnapShotStruct> snapshotStack;

    // (Fourth rule)
    /**
     * �״ε���ʱ��ʵ�ξ��Ƕ���ĸ����root_��
     * ��ϸ��Ӧ����װ�����ṩ���û��ĺ����βα���_root��
     */
    SnapShotStruct currentSnapshot{root_};
    snapshotStack.push(currentSnapshot);

    // (Fifth rule)
    while (!snapshotStack.empty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        // (Sixth rule)
        // tail recursion��ֻ��һ��stage���˲�ʡ��

        // (Seventh rule)
        if (!currentSnapshot)
        {
            // (Eighth rule)
            // �޷���ֵ���˲���ʡ��
            // (Ninth rule)
            continue;
        }
        out << currentSnapshot->data << ' ';

        // (Tenth rule)
        /**
         * �������ڵĵݹ���÷��غ�Ψһ����Ϊ���µĵݹ���ã�
         * �ʲ��ر���ϵ�(��stage)��ֱ�ӽ�����tail recursions�������ջ���ɡ�
         * ע�⵽��ĳ�εݹ���õ�ʵ��Ϊ0�����¿ղ�����������Ϊ���򲻱ؽ�ջ
         * (�������η��ʣ���ѡ)��
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
             * �����ݹ���ã�����һ��stage��ֱ�ӷ����ջ����
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
    // ��Ϊ����������Ҷ�ӽ�㣬�򷵻�0
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
        // ��Ҫ��ʼ��struct�ĳ�Ա�������޷�ʹ�ó�ʼ���б����Ƕ��幹�캯��
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
        // ��Ҫ��ʼ��struct�ĳ�Ա�������޷�ʹ�ó�ʼ���б����Ƕ��幹�캯��
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

    BinNode *this_node{};                     // ���ڴ���Ľ��
    value_type this_data = flag;              // �ݴ�����
    Queue::linkQueue<BinNode *> node_queue{}; // ��Ŵ�����(data�Ѷ���child����)���Ķ���

    // Ҫ����ն�����һ���Ϸ����ݣ���Ϊ������data
    do
    {
        std::cout << "\n����������: ";
        in >> this_data;

        // ��Ϊ�Ƿ����룬�������˴���ս���������flag����Ҫ����������
        if (std::cin.fail() || value_type_equal(this_data, flag))
        {
            in.clear();
            in.sync();
            std::cerr << "�������뺬�Ϸ����ݣ�\n";
            continue;
        }
        break;
    } while (true);

    root_ = new BinNode(this_data, 0, 0);
    node_queue.push(root_);

    while (!node_queue.empty())
    {
        // ȡ��ǰ���
        this_node = node_queue.front();
        node_queue.pop();

        // ���ն�����ǰ������child��������child������child��node_queue��ʾ������
        this_data = flag; // ��ʼ�������ݴ���
        do
        {
            std::cout << "\n�������㣺" << this_node->data << " ��left child������ " << flag << " ��ʾ�ޣ���\n";
            in >> this_data;

            // ��Ϊ�Ƿ����룬Ҫ����������
            if (in.fail())
            {
                in.clear();
                in.sync(); // ���ļ���sync()��Ϊδ���壿
                std::cerr << "�Ƿ����룡";
                continue;
            }

            // ��ָ����ǰ�������child
            if (value_type_equal(this_data, flag))
            {
                in.sync(); // ���ļ���sync()��Ϊδ���壿
                std::cout << "��ָ���ý����left child\n";
                break;
            }

            // ��ǰ�������child������child����parent�ϣ�Ȼ����child����У���ʾ��child��children������
            std::cout << "��ָ����childΪ��" << this_data << '\n';
            node_queue.push(this_node->left = new BinNode(this_data, 0, 0));

            break;
        } while (true);

        // ���ն�����ǰ������child��������child������child��node_queue��ʾ������
        this_data = flag; // ��ʼ�������ݴ���
        do
        {
            std::cout << "\n�������㣺" << this_node->data << " ��right child������ " << flag << " ��ʾ�ޣ���\n";
            in >> this_data;

            // ��Ϊ�Ƿ����룬Ҫ����������
            if (in.fail())
            {
                in.clear();
                in.sync(); // ���ļ���sync()��Ϊδ���壿
                std::cerr << "�Ƿ����룡";
                continue;
            }

            // ��ָ����ǰ�������child
            if (value_type_equal(this_data, flag))
            {
                in.sync(); // ���ļ���sync()��Ϊδ���壿
                std::cout << "��ָ���ý����right child\n";
                break;
            }

            // ��ǰ�������child������child����parent�ϣ�Ȼ����child����У���ʾ��child��children������
            std::cout << "��ָ����childΪ��" << this_data << '\n';
            node_queue.push(this_node->right = new BinNode(this_data, 0, 0));

            break;
        } while (true);

        /* ��ǰ��㴦����ϣ�׼������node_queue�е��¸���� */

    } // while (!node_queue.empty())
}

template <class T, typename Comparator>
void printBinaryTree(const binaryTree<T, Comparator> &bin_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out)
{
    if (bin_tree.empty())
    {
        out << "��һ�ÿն�����\n";
        return;
    }

    out << "(��δ�ӡ) ��ʽ��\"parent    lchild    rchild\" ( " << flag << " ��ʾ�ս�� )\n";
    Queue::seqQueue<typename binaryTree<T, Comparator>::value_type> node_data_queue{}; // ��Ŵ���ӡ���Ķ���
    /*typename*/ typename binaryTree<T, Comparator>::value_type this_data = flag;      // �ݴ浱ǰ����data
    typename binaryTree<T, Comparator>::value_type left_data = flag;                   // �ݴ���child��data
    typename binaryTree<T, Comparator>::value_type right_data = flag;                  // �ݴ���child��data

    // ������data���
    node_data_queue.push(bin_tree.root(flag));

    while (!node_data_queue.empty())
    {
        // ȡ��ǰ����data
        this_data = node_data_queue.front();
        node_data_queue.pop();

        // ���Ե�ǰdataΪdata�Ľ�������child��data������ӡ����׼����豸
        out << this_data << '\t' << (left_data = bin_tree.lchild(this_data, flag)) << '\t' << (right_data = bin_tree.rchild(this_data, flag)) << '\n';

        // ���Ե�ǰdataΪdata�Ľ����children����children��ӣ���ʾ����ӡ
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
