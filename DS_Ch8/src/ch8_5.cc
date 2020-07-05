/**
 * @file ch8_5.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 程序设计题第5题：不等概无序表顺序查找的简单优化
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

namespace Find
{
    /**
     * @brief 顺序查找一个顺序单链表
     * 
     * Returns an iterator to the first element in the range [first,last) that compares equal to val. If no such element is found, the function returns last. \n
     * The function uses operator== to compare the individual elements to val.
     * 
     * @tparam InputIterator 
     * @tparam T 
     * @param rbegin Input iterators to the initial and final positions in a sequence. \n
     * The range searched is [rbegin,rend), which contains all the elements between first and last, including the element pointed by first but not the element pointed by last.
     * @param rend Input iterators to the initial and final positions in a sequence. \n
     * The range searched is [rbegin,rend), which contains all the elements between first and last, including the element pointed by first but not the element pointed by last.
     * @param val Value to search for in the range. \n
     * T shall be a type supporting comparisons with the elements pointed by InputIterator using operator== (with the elements as left-hand side operands, and val as right-hand side).
     * @return InputIterator An iterator to the first element in the range that compares equal to val. \n
     * If no elements match, the function returns rend.
     */
    template <class InputIterator, class T>
    InputIterator rfind(InputIterator rbegin, InputIterator rend, const T &val)
    {
        const auto rfirst{rbegin};
        while (rbegin != rend)
        {
            if (*rbegin == val)
            {
                // 将目标元素向表尾移动一位，使得被查概率高的元素更靠近表尾
                if (rbegin != rfirst)
                {
                    std::iter_swap(rbegin, rbegin - 1);
                    --rbegin;
                }
                return rbegin;
            }
            ++rbegin;
        }
        return rend;
    }
} // namespace Find

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
    const std::string data_file_name("\\ch8_5.result");

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
        size_t low{10}, high{25}, num_of_points{16};
        size_t iSecret;
        for (size_t i = 0; i < num_of_points; ++i)
        {
            iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
            vec.push_back(iSecret);
        }

        // 对vec排序，并去除重复元素
        std::vector<size_t>::iterator it;
        std::sort(vec.begin(), vec.end());
        it = std::unique(vec.begin(), vec.end());
        vec.resize(std::distance(vec.begin(), it));

        // 输出vec的元素
        std::cout << "vec has " << (vec.size()) << " elements:\n";
        fout << "vec has " << (vec.size()) << " elements:\n";
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            std::cout << *it << ", ";
            fout << *it << ", ";
        }
        std::cout << '\n';
        fout << '\n';

        // 从表尾反复查找同一元素
        auto target = vec.at(0);
        for (size_t i = 0; i < vec.size(); ++i)
        {
            auto result = *Find::rfind(vec.rbegin(), vec.rend(), target);
            std::cout << "*rfind(" << target << ") = " << result << '\n';
            fout << "*rfind(" << target << ") = " << result << '\n';
        }

        // 再次输出vec的元素
        std::cout << "vec has " << (vec.size()) << " elements:\n";
        fout << "vec has " << (vec.size()) << " elements:\n";
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            std::cout << *it << ", ";
            fout << *it << ", ";
        }
        std::cout << '\n';
        fout << '\n';
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
