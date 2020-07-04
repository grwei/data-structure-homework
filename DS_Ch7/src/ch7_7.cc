/**
 * @file ch7_7.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 程序设计题第7题：实现基于最小堆的整型的优先级队列，包含功能findMin(x) 和 decreaseKey(i, value)
 * @version 0.1
 * @date 2020-07-04
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include "BinaryHeap.h"
#include <algorithm>
#include <climits>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <vector>

namespace Queue
{
    /**
     * @brief 基于最小堆的整型的优先级队列类
     * 
     */
    class priority_queue_int : public Queue::BinaryHeap<int, std::greater<int>>
    {
    public:
        priority_queue_int(const List::seqList<value_type> &items)
            : BinaryHeap(items) {}

        /**
         * @brief 找出优先级值大于等于指定值x的最小元素，返回其下标
         * 
         * @param x 指定值x
         * @return int 大于等于指定值x的最小元素的下标，0表示查找失败
         */
        size_type findMin(value_type x) const;

        /**
         * @brief 将第i个结点的优先级值减小value
         * 
         * @param i 目标元素的下标
         * @param value 优先级值的减小量
         */
        void decreaseKey(size_type i, value_type value);

        /**
         * @brief 将第i个结点的优先级值增加value
         * 
         * @param i 目标元素的下标
         * @param value 优先级值的增加量
         */
        void increaseKey(size_type i, value_type value);
    };

} // namespace Queue

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
    const std::string data_file_name("\\ch7_7.result");

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
        List::seqList<int> int_array(num_of_points);
        /* initialize random seed: */
        srand(time(NULL));

        /* generate secret number between 1 and 10: */
        int iSecret;
        for (int i = 0; i < num_of_points; ++i)
        {
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            int_array.push_back(iSecret);
        }

        int_array.traverse(std::cout);
        int_array.traverse(fout);

        // 从源数组建立一个最大堆
        Queue::priority_queue_int priority_queue(int_array);
        priority_queue.print_heap(std::cout);
        priority_queue.print_heap(fout);

        // 依次findMin
        for (size_t i = 0; i < priority_queue.size(); ++i)
        {
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            std::cout << "findMin(" << iSecret << ") = " << priority_queue.findMin(iSecret) << '\n';
            fout << "findMin(" << iSecret << ") = " << priority_queue.findMin(iSecret) << '\n';
        }

        // 全部结点加减随机数
        for (int i = 1; i <= num_of_points; ++i)
        {
            iSecret = -low + (high + low + 1) * rand() / (RAND_MAX + 1);
            priority_queue.increaseKey(i, iSecret);
        }
        std::cout << "\n全部结点加减随机数后: " << priority_queue << '\n';
        fout << "\n全部结点加减随机数后: " << priority_queue << '\n';

        // 依次出队
        std::cout << "\n依次出队: \n";
        fout << "\n依次出队: \n";
        for (int i = 0; i < num_of_points; ++i)
        {
            auto obj = priority_queue.top();
            priority_queue.pop();
            std::cout << obj << ", ";
            fout << obj << ", ";
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

typename Queue::priority_queue_int::size_type Queue::priority_queue_int::findMin(value_type x) const
{
    size_type current_index{0};
    int current_min{INT_MAX};
    for (size_type i = 1; i <= current_size_; ++i)
    {
        if (array_[i] >= x && array_[i] <= current_min)
        {
            current_min = array_[current_index = i];
        }
    }

    return current_index;
}

void Queue::priority_queue_int::decreaseKey(size_type i, value_type value)
{
    if (!value)
        return;

    array_[i] = array_[i] - value;
    if (value > 0)
        percolateUp(i);
    else
        percolateDown(i);
}

void Queue::priority_queue_int::increaseKey(size_type i, value_type value)
{
    decreaseKey(i, -value);
}
