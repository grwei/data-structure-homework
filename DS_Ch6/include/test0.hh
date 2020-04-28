/**
 * @file test0.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief ����һ���ļ���������һ�ö������Ĳ�α���(deprecated)
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
 * @brief ����һ���ļ���������һ�ö������Ĳ�α���
 * 
 * @param _file_path �ļ�·��
 * @param empty_flag �ս����
 * 
 * @details ����ѯ���Ƿ�ɾ��ͬ���ļ������У���
 * Ȼ���ж��ļ��Ƿ�����ҿɶ������ǣ������κβ�����
 * ���������½��ļ���
 * ��������true��ֻ��֤�ļ�file_path���ڣ�����֤��ɶ���
 *
 * @return true �ļ��Ѵ��ڣ������ɳɹ�
 * @return false �ļ�����ʧ��
 */
static bool GenTreeData(const char *_file_path = "./test0.txt", const char *empty_flag = "@")
{
    std::string file_path(_file_path);

    // ����DOS���ѯ���Ƿ�ɾ���ļ�
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

    // ����ļ��Ƿ�����ҿɶ�
    std::ifstream fin(file_path.c_str(), std::ios_base::in);
    if (fin.good())
    {
        std::cerr << "�ļ��Ѵ��ڣ�\n";
        fin.close();

        system("pause");
        return true;
    }

    // �ļ������ڻ򲻿ɶ��������½�
    std::ofstream fout(file_path.c_str(), std::ios_base::out);
    if (fout.fail())
    {
        std::cerr << "��дȨ�ޣ��ļ�����ʧ�ܣ�\n";

        system("pause");
        return false;
    }
    fout << "A\n"
         << "L\tC\n"
         << "B\tE\t" << empty_flag << "\tD\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << "W\t" << empty_flag << '\n'
         << empty_flag << "\tX\n"
         << empty_flag << '\t' << empty_flag << std::endl;

    // ����Ƿ����ɳɹ�
    if (fout.good())
    {
        system("echo File created successfully!");
        fout.close();
        system("pause");
        return true;
    }

    std::cerr << "�޷������ļ���\n";
    system("pause");
    return false;
}

/**
 * @brief (������)��һ�ö������ı�������嵽�����
 * 
 * @tparam T �������洢�����ݵ�����
 * @tparam Comparator �����������ڱȽ�T���͵����ݣ�lhs < rhs
 * Ҫ������bool operator(const T &lhs, const T &rhs)
 * @param binary_tree ��������Ķ���
 * @param flag ��T�Ķ��󣬱�ʾ�ս���������
 * @param out ���������Ҫ����ostream�༰��������Ķ�����std::cout����ofstream��Ķ���
 */
template <typename T, typename Comparator>
static void print_test_result(const binaryTree<T, Comparator> &binary_tree, const typename binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout)
{
    out << "�������Ĺ�ģ(�ݹ� �ǵݹ�)��\n"
        << binary_tree.size() << ' ' << binary_tree.size_loop();
    out << "\n�������ĸ�(��)��(�ݹ� �ǵݹ�)����0��\n"
        << binary_tree.height() << ' ' << binary_tree.height_loop();
    out << "\nǰ�����(�ݹ�)��\n";
    binary_tree.preOrder(out);
    out << "\nǰ�����(�ǵݹ�)��\n";
    binary_tree.preOrder_loop(out);
    out << "\n�������(�ݹ�)��\n";
    binary_tree.inOrder(out);
    out << "\n�������(�ǵݹ�)��\n";
    binary_tree.inOrder_loop(out);
    out << "\n�������(�ݹ�)��\n";
    binary_tree.postOrder(out);
    out << "\n�������(�ǵݹ�)��\n";
    binary_tree.postOrder_loop(out);
    out << "\n��α�����\n";
    binary_tree.levelOrder(out);
    out << "\n��δ�ӡ(����lchild(), rchild(), root()��API)��\n";
    printBinaryTree(binary_tree, flag, out);
}

} // namespace Tree

#endif /* INCLUDE_TEST0_HH_ */
