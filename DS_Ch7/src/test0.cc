/**
 * @file test0.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 优先级队列基本测试代码
 * @version 0.1
 * @date 2020-07-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "BinaryHeap.h"
#include <ctime>
#include <fstream>

/**
 * @brief 测试程序
 * 
 * @param argc 参数个数
 * @param argv 参数数组
 * @return int 返回值
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
        List::seqList<std::string> string_array{"1", "2", "3", "9", "8", "7", "6", "5", "4", "0"};
        string_array.traverse(std::cout);
        string_array.traverse(fout);
        Priority_queue::BinaryHeap priority_queue(string_array);

        std::string str;
        while (!priority_queue.empty())
        {
            str = priority_queue.top();
            priority_queue.pop(&str);
            std::cout << str << '\t';
            fout << str << '\t';
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
