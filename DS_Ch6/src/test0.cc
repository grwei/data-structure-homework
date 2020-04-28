/****************************************************
 * @file test0.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief ��������ʵ�ֵĶ�������(binaryTree)�Ļ������ܲ���
 * @version 0.1
 * @date 2020-04-19
 * @note ��ȡ�ļ�·�����ο���http://www.cplusplus.com/reference/string/string/find_last_of/
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
 * @brief ��������ʵ�ֵĶ�������(binaryTree)�Ĳ�������
 * 
 * @param argc �����в�������Ŀ
 * @param argv �����в���������
 * @return int 0-����
 * @warning Ҫ��.exe�������ڵ�Ŀ¼�ж�дȨ��
 * @details ���ֲ��Խ���������һ���ı��ĵ���
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

    // ��ȡ�ļ�·�����ο���http://www.cplusplus.com/reference/string/string/find_last_of/
    const std::string full_path_exec{argv[0]};
    std::string::size_type found = full_path_exec.find_last_of("/\\", std::string::npos);
    const std::string exec_path = full_path_exec.substr(0, found);
    const std::string exec_filename = full_path_exec.substr(found + 1, std::string::npos);
    const std::string data_file_name("\\test0.result");

    // �߽���ԣ����и�������
    Tree::binaryTree<std::string> binary_tree{"r"};
    binary_tree.delLeft("r");
    binary_tree.delRight("r");

    Tree::print_test_result(binary_tree, "@", std::cout);

    // ���������ļ���Ȼ����ļ��ж�ȡ���ݣ����˽���һ�ö�����
    std::string data_file_full_path{exec_path + data_file_name}; // �����ļ��ľ��Ե�ַ

    // ���������ļ�
    if (!Tree::GenTreeData(data_file_full_path.c_str(), "@"))
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
    binary_tree.createTree("@", fin);
    fin.close();

    // ׼�������д�������ļ�
    std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
    if (fout.fail())
    {
        std::cerr << "�ļ���" << data_file_full_path << "д��ʧ�ܣ�\n";
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

    std::cout << "\n��֦��\n";
    Tree::print_test_result(binary_tree, "@", std::cout);
    fout << "\n��֦��\n";
    Tree::print_test_result(binary_tree, "@", fout);

    t = clock() - t;
    // printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
    std::cout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";
    fout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";

    fout.close();
    system("pause");
    return 0;
}
