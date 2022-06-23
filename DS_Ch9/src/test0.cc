/**
 * @file test0.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 二叉查找树类的基本测试
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include <algorithm>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief 测试程序
 * 
 * @param argc 参数个数
 * @param argv 参数数组
 * @return int 返回值
 * @warning 要求.exe对其所在的目录有读写权限
 * @details 部分测试结果将输出到一个文本文档中
 */
int main(int argc, char const *argv[])
{
    auto pi = new int[100];
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

    // 打开测试数据文件
    std::string data_file_full_path{exec_path + data_file_name}; // 数据文件的绝对地址
    std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
    if (fout.fail())
    {
        std::cerr << "无写权限，测试数据文件生成失败！\n";
        system("pause");
        return false;
    }

    // output time information
    time(&rawtime);                 // Get the current calendar time
    timeinfo = localtime(&rawtime); // Convert time_t to tm as local time
    // printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string
    std::cout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';
    fout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';

    // 开始测试
    try
    {
        std::vector<size_t> vec;

        /* initialize random seed: */
        srand(time(NULL));

        /* generate secret number between low and high: */
        size_t low{10}, high{25}, num_of_points{3};
        size_t iSecret;
        for (size_t i = 0; i < num_of_points; ++i)
        {
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            vec.push_back(iSecret);
        }
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
        fout << e << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        fout << e.what() << '\n';
    }

    // output time information
    t = clock() - t;
    // printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
    std::cout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";
    fout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";

    // 测试结束
    fout.close();
    system("pause");
    return 0;
} // main
