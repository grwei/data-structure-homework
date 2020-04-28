/**
 * @file test0.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 生成一个文件，内容是一棵二叉树的层次遍历(deprecated)
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#ifndef INCLUDE_TEST0_HH_
#define INCLUDE_TEST0_HH_

#include "Tree.h"
#include <ctime>
#include <fstream>
#include <iostream>

namespace Tree
{

/**
 * @brief 生成一个文件，内容是一棵二叉树的层次遍历
 * 
 * @param _file_path 文件路径
 * @param empty_flag 空结点标记
 * 
 * @details 首先询问是否删除同名文件（若有）。
 * 然后判断文件是否存在且可读，若是，则不做任何操作；
 * 若否，则尝试新建文件。
 * 函数返回true，只保证文件file_path存在，不保证其可读。
 *
 * @return true 文件已存在，或生成成功
 * @return false 文件生成失败
 */
static bool GenTreeData(const char *_file_path = "./test0.txt", const char *empty_flag = "@")
{
    std::string file_path(_file_path);

    // 调用DOS命令，询问是否删除文件
    std::string cmd = std::string("DEL /P \"") + file_path + '"';
    system("@echo on");
    system("echo We are trying to delete some files, which will be created later.");
    system("pause");
    system(cmd.c_str());
    // system((std::string("IF NOT EXIST ") + '"' + file_path + "\" (").c_str());
    // system("echo File has been deleted!");
    // system(") ELSE (");
    // system("echo Fail to delete files!");
    // system(")");
    // system("pause");

    // 检查文件是否存在且可读
    std::ifstream fin(file_path.c_str(), std::ios_base::in);
    if (fin.good())
    {
        std::cerr << "文件已存在！\n";
        fin.close();

        system("pause");
        return true;
    }

    // 文件不存在或不可读，尝试新建
    std::ofstream fout(file_path.c_str(), std::ios_base::out);
    if (fout.fail())
    {
        std::cerr << "无写权限，文件生成失败！\n";

        system("pause");
        return false;
    }
    fout << "A\n"
         << "L\tC\n"
         << "B\tE\t" << empty_flag << "\tD\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << "W\t" << empty_flag << '\n'
         << empty_flag << "\tX\n"
         << empty_flag << '\t' << empty_flag << std::endl;

    // 检查是否生成成功
    if (fout.good())
    {
        system("echo File created successfully!");
        fout.close();
        system("pause");
        return true;
    }

    std::cerr << "无法生成文件！\n";
    system("pause");
    return false;
}

/**
 * @brief (测试用)将一棵二叉树的遍历结果插到输出流
 * 
 * @tparam T 二叉树存储的数据的类型
 * @tparam Comparator 函数对象，用于比较T类型的数据：lhs < rhs
 * 要求重载bool operator(const T &lhs, const T &rhs)
 * @param binary_tree 二叉树类的对象
 * @param flag 类T的对象，表示空结点的特殊标记
 * @param out 输出流对象，要求是ostream类及其派生类的对象，如std::cout，或ofstream类的对象
 */
template <typename T, typename Comparator>
static void print_test_result(const binaryTree<T, Comparator> &binary_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout)
{
    out << "二叉树的规模(递归 非递归)：\n"
        << binary_tree.size() << ' ' << binary_tree.size_loop();
    out << "\n二叉树的高(深)度(递归 非递归)，从0起：\n"
        << binary_tree.height() << ' ' << binary_tree.height_loop();
    out << "\n前序遍历(递归)：\n";
    binary_tree.preOrder(out);
    out << "\n前序遍历(非递归)：\n";
    binary_tree.preOrder_loop(out);
    out << "\n中序遍历(递归)：\n";
    binary_tree.inOrder(out);
    out << "\n中序遍历(非递归)：\n";
    binary_tree.inOrder_loop(out);
    out << "\n后序遍历(递归)：\n";
    binary_tree.postOrder(out);
    out << "\n后序遍历(非递归)：\n";
    binary_tree.postOrder_loop(out);
    out << "\n层次遍历：\n";
    binary_tree.levelOrder(out);
    out << "\n层次打印(调用lchild(), rchild(), root()等API)：\n";
    printBinaryTree(binary_tree, flag, out);
}

} // namespace Tree

#endif /* INCLUDE_TEST0_HH_ */
