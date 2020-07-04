/**
 * @file ch7_1.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 程序设计题第1题：实现最大堆
 * @version 0.1
 * @date 2020-07-04
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include "BinaryHeap.h"
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>

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
    const std::string data_file_name("\\ch7_1.result");

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
        int low{10}, high{99}, num_of_points{18};
        List::seqList<std::string> string_array(num_of_points);
        /* initialize random seed: */
        srand(time(NULL));

        /* generate secret number between 1 and 10: */
        int iSecret;
        for (int i = 0; i < num_of_points; ++i)
        {
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            string_array.push_back(std::to_string(iSecret));
        }

        string_array.traverse(std::cout);
        string_array.traverse(fout);

        // 从源数组建立一个最大堆
        Queue::BinaryHeap priority_queue(string_array, std::less<std::string>{});

        // 依次出队
        std::string str;
        while (!priority_queue.empty())
        {
            str = priority_queue.top();
            priority_queue.pop(&str);
            std::cout << str << ", ";
            fout << str << ", ";
        }

        std::cout << "\n队空? "
                  << std::boolalpha << priority_queue.empty() << '\n';
        fout << "\n队空? "
             << std::boolalpha << priority_queue.empty() << '\n';

        // 逐元素入队建立最大堆
        for (int i = 0; i < num_of_points; ++i)
        {
            priority_queue.push(string_array[i]);
        }

        // 依次出队
        while (!priority_queue.empty())
        {
            str = priority_queue.top();
            priority_queue.pop(&str);
            std::cout << str << ", ";
            fout << str << ", ";
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
}
