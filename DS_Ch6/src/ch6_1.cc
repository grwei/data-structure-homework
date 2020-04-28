/**
 * @file ch6_1.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief ���ԣ����������������н�����������
 * @version 0.1
 * @date 2020-04-27
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include "binaryTree.hh"
#include <ctime>
#include <fstream>
#include <string>

/**
 * @brief ����һ���ļ���������һ�ö������Ĳ�α���
 * 
 * @param _file_path �ļ�·��
 * @param empty_flag �ս����
 * 
 * @details ����ѯ���Ƿ�ɾ��ͬ���ļ������У���
 * \Ȼ���ж��ļ��Ƿ�����ҿɶ������ǣ������κβ�����
 * \���������½��ļ���
 * \��������true��ֻ��֤�ļ�file_path���ڣ�����֤��ɶ���
 *
 * @return true �ļ��Ѵ��ڣ������ɳɹ�
 * @return false �ļ�����ʧ��
 */
static bool GenTreeData(const char *_file_path = "./test0.txt", const char *empty_flag = "@");

/**
 * @brief (������)����������Ķ��ַ���������嵽�����
 * 
 * @tparam T �������洢�����ݵ�����
 * @tparam Comparator �����������ڱȽ�T���͵����ݣ�lhs < rhs
 * @note Ҫ������bool operator(const T &lhs, const T &rhs)
 * 
 * @param binary_tree ��������Ķ���
 * @param flag ��T�Ķ��󣬱�ʾ�ս���������
 * @param out ���������Ҫ����ostream�༰��������Ķ�����std::cout����ofstream��Ķ���
 * 
 */
template <typename T, typename Comparator>
static void print_test_result(const Tree::binaryTree<T, Comparator> &binary_tree, const typename Tree::binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout);

int main(int argc, char const *argv[])
{
    // time
    clock_t t = clock();
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);                 // Get the current calendar time
    timeinfo = localtime(&rawtime); // Convert time_t to tm as local time

    // ��ȡ�ļ�·�����ο���http://www.cplusplus.com/reference/string/string/find_last_of/
    const std::string full_path_exec{argv[0]};
    std::string::size_type found = full_path_exec.find_last_of("/\\", std::string::npos);
    const std::string exec_path = full_path_exec.substr(0, found + 1);
    const std::string exec_filename = full_path_exec.substr(found + 1, std::string::npos);
    const std::string data_file_name("ch6_1.result");

    // ���������ļ���Ȼ����ļ��ж�ȡ���ݣ����˽���һ�ö�����
    std::string data_file_full_path{exec_path + data_file_name}; // �����ļ��ľ��Ե�ַ

    // ���������ļ�
    if (!GenTreeData(data_file_full_path.c_str(), "@"))
    {
        std::cout << "�ļ���" << data_file_full_path << "����ʧ�ܣ�\n";
        return 1;
    }

    // �������ļ�
    std::ifstream fin(data_file_full_path.c_str(), std::ios_base::in);
    if (fin.fail())
    {
        std::cout << "�ļ���" << data_file_full_path << "��ȡʧ�ܣ�\n";
        return 1;
    }

    // ����������
    Tree::binaryTree<std::string> binary_tree{};
    binary_tree.createTree("@", fin);
    fin.close();

    // ׼�������д�������ļ�
    std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
    if (fout.fail())
    {
        std::cerr << "�ļ���" << data_file_full_path << "д��ʧ�ܣ�\n";
        return 1;
    }

    // printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string
    std::cout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';
    fout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';

    print_test_result(binary_tree, "@", std::cout);
    print_test_result(binary_tree, "@", fout);

    // ch6_1
    binary_tree.swaplr();
    std::cout << "\n�������ҽ���\n";
    fout << "\n�������ҽ���\n";
    print_test_result(binary_tree, "@", std::cout);
    print_test_result(binary_tree, "@", fout);

    t = clock() - t;
    // printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
    std::cout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";
    fout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";

    fout.close();
    system("pause");
    return 0;
}

bool GenTreeData(const char *_file_path, const char *empty_flag)
{
    std::string file_path(_file_path);

    // ����DOS���ѯ���Ƿ�ɾ���ļ�
    std::string cmd = std::string("DEL /P \"") + file_path + '"';
    system("@echo on");
    system("echo We are trying to delete some files, which will be created later.");
    system("pause");
    system(cmd.c_str());

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

template <class T, typename Comparator>
void print_test_result(const Tree::binaryTree<T, Comparator> &binary_tree, const typename Tree::binaryTree<T, Comparator>::value_type &flag, std::ostream &out)
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
    Tree::printBinaryTree(binary_tree, flag, out);
}
