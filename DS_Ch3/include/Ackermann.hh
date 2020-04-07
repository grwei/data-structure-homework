/**
 * @file Ackermann.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief Ackermann库
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __ACKERMANN_HH__
#define __ACKERMANN_HH__

#include "Stack.hh"
#include <climits>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>

/**
 * @brief 实现AckerMann函数。
 * 
 * @details 两种方式: 
 * - 递归调用(系统栈) 
 * - 堆栈模拟(堆栈) 
 * 
 */
class Akm_t
{
private:
    /**
     * @brief 对象标识
     * 
     * @details 无实际作用
     * 
     */
    std::string _name;

    /**
     * @brief Ackermann函数递归版本
     * 
     * @details 是工具函数
     * 
     * @param m 第一个参数, 建议取1 ~ 4
     * @param n 第二个参数, 建议取1 ~ 13
     * @return int 计算结果
     */
    static int Ackermann(int m, int n);

    /**
     * @brief Ackermann函数堆栈模拟递归版本
     * 
     * @details 是工具函数
     * 
     * @param m 第一个参数, 建议取1 ~ 4
     * @param n 第二个参数, 建议取1 ~ 13
     * @return int 计算结果
     */
    static int AckermannLoop(int m, int n);

    /**
     * @brief 初始化类内部的静态计数器
     * 
     */
    static void AkmInit() { Akm_deep = deep_max = 0; }

    static int Akm_deep; ///< 记录当前递归深度
    static int deep_max; ///< 记录最大递归深度

public:
    /**
     * @brief Construct a new Akm_t object
     * 
     * @param name 对象标识符. 
     * 
     * @details 传入的参数不会被使用
     * 
     */
    Akm_t(std::string name = "name") : _name(name) {}

    /**
     * @brief Destroy the Akm_t object
     * 
     */
    ~Akm_t() = default;

    /**
     * @brief 堆栈版本的Ackermann函数
     * 
     * @param x 参数1, 建议取1 ~ 4
     * @param y 参数2, 建议取1 ~ 13
     * 
     * @details 将会半实时刷新当前堆栈深度。当最大深度增加时, 刷新显示内容
     *
     */
    static void Akm_loop(int x, int y);

    /**
     * @brief 递归版本的Ackermann函数
     * 
     * @param x 参数1, 建议取1 ~ 4
     * @param y 参数2, 建议取1 ~ 13
     * 
     * @details 将会半实时刷新当前递归深度。当最大深度增加时, 刷新显示内容
     *
     */
    static void Akm_rec(int x, int y);
};

// 静态数据成员需要在类外定义和初始化
int Akm_t::Akm_deep = 0;
int Akm_t::deep_max = 0;

void Akm_t::Akm_loop(int x, int y)
{
    AkmInit();

    clock_t t;
    int result;

    t = clock();
    result = AckermannLoop(x, y);
    t = clock() - t;

    printf("\nAckermannLoop(%i, %i) = %i\n", x, y, result);
    printf("AckermannLoop(%i, %i) took %ld clicks (%f seconds).\n", x, y, t, ((float)t) / CLOCKS_PER_SEC);
}

void Akm_t::Akm_rec(int x, int y)
{
    AkmInit();

    clock_t t;
    int result;

    t = clock(); // Returns the processor time consumed by the program.
    std::cout << "\nCurrent call:\n";
    result = Ackermann(x, y);
    std::cout << "Current deep: " << std::scientific << std::setw(10) << std::left << Akm_deep << " Max deep: " << std::setw(10) << deep_max;
    std::cout << "\nRecursion terminated.\n";
    t = clock() - t;

    printf("\nAckermann(%i, %i) = %i\n", x, y, result);
    printf("Ackermann(%i, %i) took %ld clicks (%f seconds).\n", x, y, t, ((float)t) / CLOCKS_PER_SEC);
}

int Akm_t::Ackermann(int m, int n)
{
    static time_t begTime = time(nullptr);

    if (++Akm_t::Akm_deep > Akm_t::deep_max)
    {
        ++Akm_t::deep_max;
        std::cout << "Max deep: " << std::setw(10) << std::left << std::setw(10) << Akm_t::deep_max << "Time(s): " << std::defaultfloat << difftime(time(nullptr), begTime) << '\r';
    }
    // std::cout << "Current deep: " << std::setw(10) << std::left << Akm_deep << " Max deep: " << std::setw(10) << deep_max << '\r';
    // printf("m = %-10.7g n = %-10.7g\r", (float)m, (float)n);
    // std::cout << "m = " << std::setw(10) << std::left << m << "n = " << std::setw(10) << std::left << n << '\r';
    if (!m)
    {
        --Akm_t::Akm_deep;
        return n + 1;
    }
    if (!n)
    {
        --Akm_t::Akm_deep;
        return Ackermann(m - 1, 1);
    }

    int midVal = Ackermann(m, n - 1);

    --Akm_t::Akm_deep;
    return Ackermann(m - 1, midVal);
}

int Akm_t::AckermannLoop(int m, int n)
{
    time_t begTime = time(nullptr);

    struct SnapShotStruct
    {
        int m;
        int n;
        int stage;
    };

    int retVal;

    Stack::seqStack<SnapShotStruct> SnapShotStack;
    SnapShotStruct currentSnapshot{m, n, 0};
    SnapShotStack.push(currentSnapshot);

    std::cout << "Current top:\n";
    while (!SnapShotStack.isEmpty())
    {
        currentSnapshot = SnapShotStack.top();
        SnapShotStack.pop();
        if ((Akm_t::Akm_deep = SnapShotStack.size()) > Akm_t::deep_max)
        {
            ++Akm_t::deep_max;
            // std::cout << "m = " << std::setw(10) << std::left << currentSnapshot.m << "n = " << std::setw(10) << currentSnapshot.n << " Current deep: " << std::setw(10) << Akm_deep << " Max deep: " << std::setw(10) << deep_max << '\r';
            std::cout << "Max deep: " << std::setw(10) << std::left << std::setw(10) << Akm_t::deep_max << "Stack size(kB): " << std::setw(10) << SnapShotStack.elemMem() / 1024 << "Time(s): " << difftime(time(nullptr), begTime) << '\r';
        }
        // printf("m = %-10.7g n = %-10.7g\r", (float)currentSnapshot.m, (float)currentSnapshot.n);
        switch (currentSnapshot.stage)
        {
        case 0:
        {
            if (!currentSnapshot.m)
            {
                retVal = currentSnapshot.n + 1;
                continue;
            }

            if (!currentSnapshot.n)
            {
                SnapShotStruct newSnapshot{currentSnapshot.m - 1, 1, 0};
                SnapShotStack.push(newSnapshot);
                continue;
            }

            currentSnapshot.stage = 1;
            SnapShotStack.push(currentSnapshot);
            SnapShotStruct newSnapshot{currentSnapshot.m, currentSnapshot.n - 1, 0};
            SnapShotStack.push(newSnapshot);
            continue;
        }
        break;

        case 1:
        {
            SnapShotStruct newSnapshot{currentSnapshot.m - 1, retVal, 0};
            SnapShotStack.push(newSnapshot);
            continue;
        }
        break;
        } // switch
    }     // while

    std::cout << "Current deep: " << std::scientific << std::setw(10) << std::left << std::setw(10) << Akm_t::Akm_deep << " Max deep: " << std::setw(10) << Akm_t::deep_max << "Stack size(kB): " << std::setw(10) << SnapShotStack.elemMem() / 1024;
    std::cout << "\nStack's cleared.\n";
    return retVal;
}

#endif
