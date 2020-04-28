/****************************************************
 * @file test0.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 二叉链表实现的二叉树类(binaryTree)的基本功能测试
 * @version 0.1
 * @date 2020-04-19
 * @note 读取文件路径，参考：http://www.cplusplus.com/reference/string/string/find_last_of/
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 * @note Reference
 * -# http://www.cplusplus.com/reference/string/string/find_last_of/
 * -# http://www.cplusplus.com/reference/ctime/clock/
 * -# http://www.cplusplus.com/reference/ctime/localtime/
 * 
 ****************************************************/

#include "test0.hh"

/**
 * @brief 二叉链表实现的二叉树类(binaryTree)的测试例程
 * 
 * @param argc 命令行参数的数目
 * @param argv 命令行参数的内容
 * @return int 0-正常
 * @warning 要求.exe对其所在的目录有读写权限
 * @details 部分测试结果将输出到一个文本文档中
 * 
 * @note Reference
 * -# http://www.cplusplus.com/reference/string/string/find_last_of/
 * -# http://www.cplusplus.com/reference/ctime/clock/
 * -# http://www.cplusplus.com/reference/ctime/localtime/
 */
int main(int argc, char const *argv[])
{
    // time
    clock_t t = clock();
    time_t rawtime;
    struct tm *timeinfo;

    // 获取文件路径，参考：http://www.cplusplus.com/reference/string/string/find_last_of/
    const std::string full_path_exec{argv[0]};
    std::string::size_type found = full_path_exec.find_last_of("/\\", std::string::npos);
    const std::string exec_path = full_path_exec.substr(0, found);
    const std::string exec_filename = full_path_exec.substr(found + 1, std::string::npos);
    const std::string data_file_name("\\test0.result");

    // 边界测试：仅有根结点的树
    Tree::binaryTree<std::string> binary_tree{"r"};
    binary_tree.delLeft("r");
    binary_tree.delRight("r");

    Tree::print_test_result(binary_tree, "@", std::cout);

    // 生成数据文件，然后从文件中读取数据，依此建立一棵二叉树
    std::string data_file_full_path{exec_path + data_file_name}; // 数据文件的绝对地址

    // 生成数据文件
    if (!Tree::GenTreeData(data_file_full_path.c_str(), "@"))
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
    binary_tree.createTree("@", fin);
    fin.close();

    // 准备将结果写入数据文件
    std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
    if (fout.fail())
    {
        std::cerr << "文件：" << data_file_full_path << "写入失败！\n";
        return 1;
    }

    time(&rawtime);                 // Get the current calendar time
    timeinfo = localtime(&rawtime); // Convert time_t to tm as local time
    // printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string

    std::cout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';
    fout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';

    Tree::print_test_result(binary_tree, "@", std::cout);
    Tree::print_test_result(binary_tree, "@", fout);

    binary_tree.delLeft("L");
    binary_tree.delRight("C");
    binary_tree.delLeft("C");

    std::cout << "\n剪枝后：\n";
    Tree::print_test_result(binary_tree, "@", std::cout);
    fout << "\n剪枝后：\n";
    Tree::print_test_result(binary_tree, "@", fout);

    t = clock() - t;
    // printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
    std::cout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";
    fout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";

    fout.close();
    system("pause");
    return 0;
}
