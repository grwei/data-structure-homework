/**
 * @file ch6_6.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief ���ԣ��ж����ö������Ƿ�Ϊ����
 * @version 0.1
 * @date 2020-04-28
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

// ��������
const std::string data_file_name("ch6_6.result"); ///< ����������ݵ��ļ���

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
 * @param tree_original ��������Ķ���
 * @param flag ��T�Ķ��󣬱�ʾ�ս���������
 * @param out ���������Ҫ����ostream�༰��������Ķ�����std::cout����ofstream��Ķ���
 */
template <typename T, typename Comparator>
static void print_test_result(const Tree::binaryTree<T, Comparator> &tree_original, const typename Tree::binaryTree<T, Comparator>::value_type &flag, std::ostream &out = std::cout);

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
    Tree::binaryTree<std::string> tree_original{};
    tree_original.createTree("@", fin);
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

    print_test_result(tree_original, "@", std::cout);
    print_test_result(tree_original, "@", fout);

    // ch6_1
    Tree::binaryTree<std::string> temp_tree = tree_original;
    temp_tree.swaplr();
    auto tree_swaplr = temp_tree;
    std::cout << "\n�������ҽ���\n";
    fout << "\n�������ҽ���\n";
    print_test_result(tree_swaplr, "@", std::cout);
    print_test_result(tree_swaplr, "@", fout);

    // ch6_3, ch6_4
    temp_tree.delLeft("G");
    temp_tree.delRight("G");
    auto tree_swaplr_and_prune = temp_tree;
    std::cout << "\n��֦��\n";
    fout << "\n��֦��\n";
    print_test_result(tree_swaplr_and_prune, "@", std::cout);
    print_test_result(tree_swaplr_and_prune, "@", fout);

    // ch6_5
    std::cout << "\ntree_swaplr == tree_swaplr_and_prune?\n"
              << std::boolalpha << (tree_swaplr == tree_swaplr_and_prune);
    fout << "\ntree_swaplr == tree_swaplr_and_prune?\n"
         << std::boolalpha << (tree_swaplr == tree_swaplr_and_prune);
    std::cout << "\ntree_original == tree_swaplr_and_prune?\n"
              << std::boolalpha << (tree_original == tree_swaplr_and_prune);
    fout << "\ntree_original == tree_swaplr_and_prune?\n"
         << std::boolalpha << (tree_original == tree_swaplr_and_prune);
    std::cout << "\ntree_original == tree_swaplr?\n"
              << std::boolalpha << (tree_original == tree_swaplr);
    fout << "\ntree_original == tree_swaplr?\n"
         << std::boolalpha << (tree_original == tree_swaplr);
    std::cout << "\ntree_original == tree_original?\n"
              << std::boolalpha << (tree_original == tree_original);
    fout << "\ntree_original == tree_original?\n"
         << std::boolalpha << (tree_original == tree_original);
    std::cout << "\ntree_swaplr == tree_swaplr?\n"
              << std::boolalpha << (tree_swaplr == tree_swaplr);
    fout << "\ntree_swaplr == tree_swaplr?\n"
         << std::boolalpha << (tree_swaplr == tree_swaplr);
    std::cout << "\ntree_swaplr_and_prune == tree_swaplr_and_prune?\n"
              << std::boolalpha << (tree_swaplr_and_prune == tree_swaplr_and_prune);
    fout << "\ntree_swaplr_and_prune == tree_swaplr_and_prune?\n"
         << std::boolalpha << (tree_swaplr_and_prune == tree_swaplr_and_prune) << '\n';

    //ch6_6
    std::cout << "\nis_symmetrical_tree(tree_original, tree_swaplr)?\n"
              << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_original, tree_swaplr);
    fout << "\nis_symmetrical_tree(tree_original, tree_swaplr)?\n"
         << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_original, tree_swaplr);
    std::cout << "\nis_symmetrical_tree(tree_swaplr, tree_swaplr)?\n"
              << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_swaplr, tree_swaplr);
    fout << "\nis_symmetrical_tree(tree_swaplr, tree_swaplr)?\n"
         << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_swaplr, tree_swaplr);
    std::cout << "\nis_symmetrical_tree(tree_original, tree_original)?\n"
              << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_original, tree_original);
    fout << "\nis_symmetrical_tree(tree_original, tree_original)?\n"
         << std::boolalpha << Tree::binaryTree<std::string>::is_symmetrical_tree(tree_original, tree_original) << '\n';

    // ���Ը�ֵ��������ƶ���ֵ���ƶ�����
    // ���ƹ���
    auto tree_copy_construct = tree_swaplr_and_prune;
    std::cout << "\n(���ƹ���)auto tree_copy_construct = tree_swaplr_and_prune;\n";
    fout << "\n(���ƹ���)auto tree_copy_construct = tree_swaplr_and_prune;\n";
    print_test_result(tree_copy_construct, "@", std::cout);
    print_test_result(tree_copy_construct, "@", fout);
    // �ƶ�����
    auto tree_move_construct = std::move(tree_swaplr_and_prune);
    std::cout << "\n(�ƶ�����)auto tree_move_construct = std::move(tree_swaplr_and_prune);\n";
    fout << "\n(�ƶ�����)auto tree_move_construct = std::move(tree_swaplr_and_prune);\n";
    print_test_result(tree_move_construct, "@", std::cout);
    print_test_result(tree_move_construct, "@", fout);
    // ��ͼʹ�ù��ڵĶ���
    std::cout << "\n(ʹ�ù��ڵĶ���)print_test_result(tree_swaplr_and_prune, \"@\", std::cout);\n";
    fout << "\n(ʹ�ù��ڵĶ���)print_test_result(tree_swaplr_and_prune, \"@\", fout);\n";
    print_test_result(tree_swaplr_and_prune, "@", std::cout);
    print_test_result(tree_swaplr_and_prune, "@", fout);
    // ���ƹ���һ����ʱ����Ȼ������ڵĶ����ƶ���ֵ
    tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);
    std::cout << "\n(����ڵĶ����ƶ���ֵ)tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);\n";
    fout << "\n(����ڵĶ����ƶ���ֵ)tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);\n";
    print_test_result(tree_swaplr_and_prune, "@", std::cout);
    print_test_result(tree_swaplr_and_prune, "@", fout);
    // ��ֵ
    Tree::binaryTree<std::string> tree_copy_assign{};
    tree_copy_assign = tree_swaplr_and_prune;
    std::cout << "\n(��ֵ)tree_copy_assign = tree_swaplr_and_prune;\n";
    fout << "\n(��ֵ)tree_copy_assign = tree_swaplr_and_prune;\n";
    print_test_result(tree_copy_assign, "@", std::cout);
    print_test_result(tree_copy_assign, "@", fout);

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
         << "B\tC\n"
         << "D\tE\tF\tG\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << "H\tI\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << std::endl;

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
void print_test_result(const Tree::binaryTree<T, Comparator> &tree_original, const typename Tree::binaryTree<T, Comparator>::value_type &flag, std::ostream &out)
{
    out << "�������Ĺ�ģ(�ݹ� �ǵݹ�)��\n"
        << tree_original.size() << ' ' << tree_original.size_loop();
    out << "\n�������ĸ�(��)��(�ݹ� �ǵݹ�)����0��\n"
        << tree_original.height() << ' ' << tree_original.height_loop();
    // ch6_2
    out << "\n��Ϊ2�Ľ��ĸ����ǣ�\n"
        << tree_original.CountDegreeTwo();
    // ch6_3
    out << "\n�Ƿ�Ϊ����������\n"
        << std::boolalpha << tree_original.isFullBinaryTree();
    // ch6_4
    out << "\n�Ƿ�Ϊ��ȫ��������\n"
        << std::boolalpha << tree_original.isCompleteTree();
    out << "\nǰ�����(�ݹ�)��\n";
    tree_original.preOrder(out);
    out << "\nǰ�����(�ǵݹ�)��\n";
    tree_original.preOrder_loop(out);
    out << "\n�������(�ݹ�)��\n";
    tree_original.inOrder(out);
    out << "\n�������(�ǵݹ�)��\n";
    tree_original.inOrder_loop(out);
    out << "\n�������(�ݹ�)��\n";
    tree_original.postOrder(out);
    out << "\n�������(�ǵݹ�)��\n";
    tree_original.postOrder_loop(out);
    out << "\n��α�����\n";
    tree_original.levelOrder(out);
    out << "\n��δ�ӡ(����lchild(), rchild(), root()��API)��\n";
    Tree::printBinaryTree(tree_original, flag, out);
}
