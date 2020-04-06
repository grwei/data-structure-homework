/****************************************************
 * @file test0.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 测试队列类的基本功能
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#include "Queue.h"
#include <iostream>
#include <string>

/**
 * @brief 用于测试队列的简单类
 * 
 * 含有两个字段和一个打印字段到屏幕的公有函数
 */
struct data_t
{
    size_t _id;        ///< size_t
    std::string _name; ///< std::string

    /**
     * @brief Construct a new data t object
     * 
     * @param id size_t
     * @param name std::string
     */
    data_t(size_t id = 0, std::string name = "name")
        : _id(id), _name(name) {}

    /**
     * @brief print
     * 
     */
    void prn() const
    {
        std::cout << "_id: " << _id << " _name: " << _name << std::endl;
    }
};

/**
 * @brief 测试队列类的基本功能
 * 
 * @param argc 命令行参数的数目
 * @param argv 命令行参数的内容
 * @return int 0-正常结束, 1-异常终止
 * 
 * @note 此例程不使用命令行参数
 * 
 * @details 测试方法: 对3种队列, 先入队5个元素, 再全部出队
 * 
 */
int main(int argc, char const *argv[])
{
    Queue::seqQueue<data_t> seqQ(1);   ///< 循环队列
    Queue::linkQueue<data_t> linQ;     ///< 链接队列
    Queue::vecQueue<data_t> vecQ(1);   ///< 顺序队列
    data_t _Data[5] = {1, 2, 3, 4, 5}; ///< 测试数据

    // 入队测试: 复制/移动
    for (int i = 0; i < 5; ++i)
    {
        seqQ.enQueue(data_t(i)); ///< 复制入队(enQueue()未实现右值版本)
        linQ.push(data_t(i));    ///< 移动入队
        vecQ.enQueue(_Data[i]);  ///< 复制入队
    }

    std::cout << "\n入队5个元素的size: \n"
              << seqQ.size() << ' ' << linQ.size() << ' ' << vecQ.size() << std::endl;

    // 出队测试
    std::cout << "\nseqQ出队: \n";
    while (!seqQ.empty())
        seqQ.deQueue().prn();

    std::cout << "\nlinQ出队: \n";
    while (!linQ.isEmpty())
    {
        auto tmp = linQ.front();
        linQ.pop();
        tmp.prn();
    }

    std::cout << "\nvecQ出队: \n";
    while (!vecQ.empty())
    {
        vecQ.deQueue().prn();
    }

    std::cout << "\n所有元素出队后的size: \n"
              << seqQ.size() << ' ' << linQ.size() << ' ' << vecQ.size() << std::endl;

    return 0;
}
