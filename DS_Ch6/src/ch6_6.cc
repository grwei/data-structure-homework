/**
 * @file ch6_6.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 测试：判断两棵二叉树是否互为镜像
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

// 常量定义
const std::string data_file_name("ch6_6.result"); ///< 保存测试数据的文件名

/**
 * @brief 生成一个文件，内容是一棵二叉树的层次遍历
 * 
 * @param _file_path 文件路径
 * @param empty_flag 空结点标记
 * 
 * @details 首先询问是否删除同名文件（若有）。
 * \然后判断文件是否存在且可读，若是，则不做任何操作；
 * \若否，则尝试新建文件。
 * \函数返回true，只保证文件file_path存在，不保证其可读。
 *
 * @return true 文件已存在，或生成成功
 * @return false 文件生成失败
 */
static bool GenTreeData(const char *_file_path = "./test0.txt", const char *empty_flag = "@");

/**
 * @brief (测试用)将二叉树类的多种方法的输出插到输出流
 * 
 * @tparam T 二叉树存储的数据的类型
 * @tparam Comparator 函数对象，用于比较T类型的数据：lhs < rhs
 * @note 要求重载bool operator(const T &lhs, const T &rhs)
 * @param tree_original 二叉树类的对象
 * @param flag 类T的对象，表示空结点的特殊标记
 * @param out 输出流对象，要求是ostream类及其派生类的对象，如std::cout，或ofstream类的对象
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

    // 获取文件路径，参考：http://www.cplusplus.com/reference/string/string/find_last_of/
    const std::string full_path_exec{argv[0]};
    std::string::size_type found = full_path_exec.find_last_of("/\\", std::string::npos);
    const std::string exec_path = full_path_exec.substr(0, found + 1);
    const std::string exec_filename = full_path_exec.substr(found + 1, std::string::npos);

    // 生成数据文件，然后从文件中读取数据，依此建立一棵二叉树
    std::string data_file_full_path{exec_path + data_file_name}; // 数据文件的绝对地址

    // 生成数据文件
    if (!GenTreeData(data_file_full_path.c_str(), "@"))
    {
        std::cout << "文件：" << data_file_full_path << "生成失败！\n";
        return 1;
    }

    // 读数据文件
    std::ifstream fin(data_file_full_path.c_str(), std::ios_base::in);
    if (fin.fail())
    {
        std::cout << "文件：" << data_file_full_path << "读取失败！\n";
        return 1;
    }

    // 建立二叉树
    Tree::binaryTree<std::string> tree_original{};
    tree_original.createTree("@", fin);
    fin.close();

    // 准备将结果写入数据文件
    std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
    if (fout.fail())
    {
        std::cerr << "文件：" << data_file_full_path << "写入失败！\n";
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
    std::cout << "\n交换左右结点后：\n";
    fout << "\n交换左右结点后：\n";
    print_test_result(tree_swaplr, "@", std::cout);
    print_test_result(tree_swaplr, "@", fout);

    // ch6_3, ch6_4
    temp_tree.delLeft("G");
    temp_tree.delRight("G");
    auto tree_swaplr_and_prune = temp_tree;
    std::cout << "\n剪枝后：\n";
    fout << "\n剪枝后：\n";
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

    // 测试赋值运算符、移动赋值和移动构造
    // 复制构造
    auto tree_copy_construct = tree_swaplr_and_prune;
    std::cout << "\n(复制构造)auto tree_copy_construct = tree_swaplr_and_prune;\n";
    fout << "\n(复制构造)auto tree_copy_construct = tree_swaplr_and_prune;\n";
    print_test_result(tree_copy_construct, "@", std::cout);
    print_test_result(tree_copy_construct, "@", fout);
    // 移动构造
    auto tree_move_construct = std::move(tree_swaplr_and_prune);
    std::cout << "\n(移动构造)auto tree_move_construct = std::move(tree_swaplr_and_prune);\n";
    fout << "\n(移动构造)auto tree_move_construct = std::move(tree_swaplr_and_prune);\n";
    print_test_result(tree_move_construct, "@", std::cout);
    print_test_result(tree_move_construct, "@", fout);
    // 试图使用过期的对象
    std::cout << "\n(使用过期的对象)print_test_result(tree_swaplr_and_prune, \"@\", std::cout);\n";
    fout << "\n(使用过期的对象)print_test_result(tree_swaplr_and_prune, \"@\", fout);\n";
    print_test_result(tree_swaplr_and_prune, "@", std::cout);
    print_test_result(tree_swaplr_and_prune, "@", fout);
    // 复制构造一个临时对象，然后向过期的对象移动赋值
    tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);
    std::cout << "\n(向过期的对象移动赋值)tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);\n";
    fout << "\n(向过期的对象移动赋值)tree_swaplr_and_prune = Tree::binaryTree(tree_move_construct);\n";
    print_test_result(tree_swaplr_and_prune, "@", std::cout);
    print_test_result(tree_swaplr_and_prune, "@", fout);
    // 赋值
    Tree::binaryTree<std::string> tree_copy_assign{};
    tree_copy_assign = tree_swaplr_and_prune;
    std::cout << "\n(赋值)tree_copy_assign = tree_swaplr_and_prune;\n";
    fout << "\n(赋值)tree_copy_assign = tree_swaplr_and_prune;\n";
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

    // 调用DOS命令，询问是否删除文件
    std::string cmd = std::string("DEL /P \"") + file_path + '"';
    system("@echo on");
    system("echo We are trying to delete some files, which will be created later.");
    system("pause");
    system(cmd.c_str());

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
         << "B\tC\n"
         << "D\tE\tF\tG\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << "H\tI\n"
         << empty_flag << '\t' << empty_flag << '\t' << empty_flag << '\t' << empty_flag << std::endl;

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

template <class T, typename Comparator>
void print_test_result(const Tree::binaryTree<T, Comparator> &tree_original, const typename Tree::binaryTree<T, Comparator>::value_type &flag, std::ostream &out)
{
    out << "二叉树的规模(递归 非递归)：\n"
        << tree_original.size() << ' ' << tree_original.size_loop();
    out << "\n二叉树的高(深)度(递归 非递归)，从0起：\n"
        << tree_original.height() << ' ' << tree_original.height_loop();
    // ch6_2
    out << "\n度为2的结点的个数是：\n"
        << tree_original.CountDegreeTwo();
    // ch6_3
    out << "\n是否为满二叉树：\n"
        << std::boolalpha << tree_original.isFullBinaryTree();
    // ch6_4
    out << "\n是否为完全二叉树：\n"
        << std::boolalpha << tree_original.isCompleteTree();
    out << "\n前序遍历(递归)：\n";
    tree_original.preOrder(out);
    out << "\n前序遍历(非递归)：\n";
    tree_original.preOrder_loop(out);
    out << "\n中序遍历(递归)：\n";
    tree_original.inOrder(out);
    out << "\n中序遍历(非递归)：\n";
    tree_original.inOrder_loop(out);
    out << "\n后序遍历(递归)：\n";
    tree_original.postOrder(out);
    out << "\n后序遍历(非递归)：\n";
    tree_original.postOrder_loop(out);
    out << "\n层次遍历：\n";
    tree_original.levelOrder(out);
    out << "\n层次打印(调用lchild(), rchild(), root()等API)：\n";
    Tree::printBinaryTree(tree_original, flag, out);
}
