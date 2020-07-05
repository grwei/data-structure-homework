/**
 * @file ch8_1.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 程序设计题第1题：以递归实现二分查找
 * @version 0.1
 * @date 2020-07-04
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include "Set.h"
#include <algorithm>
#include <climits>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief 二分查找（递归版本）
 * 
 * @tparam Key_T 键值的类型
 * @tparam Other_T 其他值的类型
 * @param data 有序表
 * @param low 查找范围下边界，即查[low, high]
 * @param high 查找范围上边界，即查[low, high]
 * @param x 目标键值
 * @return size_t 目标在表中的下标。high - low + 1表示查找失败
 */
template <class Key_T, class Other_T>
size_t binarySearch(Set::Set<Key_T, Other_T> data[], size_t low, size_t high, const Key_T &x)
{
    // 查找失败
    if (low > high)
        return high - low + 1;

    size_t mid{(low + high) / 2};
    if (x > data[mid].key_)
        return binarySearch(data, mid + 1, high, x);
    if (x < data[mid].key_)
        return binarySearch(data, low, mid - 1, x);
    return mid;
}

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
    // time
    clock_t t = clock();
    time_t rawtime;
    struct tm *timeinfo;

    // 获取文件路径，参考：http://www.cplusplus.com/reference/string/string/find_last_of/
    const std::string full_path_exec{argv[0]};
    std::string::size_type found = full_path_exec.find_last_of("/\\", std::string::npos);
    const std::string exec_path = full_path_exec.substr(0, found);
    const std::string exec_filename = full_path_exec.substr(found + 1, std::string::npos);
    const std::string data_file_name("\\ch8_1.result");

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
        std::vector<Set::Set<size_t>> vector_size_t;

        /* initialize random seed: */
        srand(time(NULL));

        /* generate secret number between low and high: */
        size_t low{10}, high{99}, num_of_points{18};
        size_t iSecret;
        for (size_t i = 0; i < num_of_points; ++i)
        {
            // 第0个元素不参与查找，以符合binarySearch接口要求
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            vector_size_t.push_back(Set::Set<size_t>{iSecret});
        }

        // 先排序
        std::sort(vector_size_t.begin(), vector_size_t.end(), std::less<Set::Set<size_t>>{});

        // 开始查找
        for (size_t i = 0; i < vector_size_t.size(); ++i)
        {
            std::cout << "binarySearch(" << vector_size_t.at(i).key_ << ") = " << binarySearch(vector_size_t.data(), 0, vector_size_t.size() - 1, vector_size_t.at(i).key_) << '\n';
            fout << "binarySearch(" << vector_size_t.at(i).key_ << ") = " << binarySearch(vector_size_t.data(), 0, vector_size_t.size() - 1, vector_size_t.at(i).key_) << '\n';
        }
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
        fout << e << '\n';
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
