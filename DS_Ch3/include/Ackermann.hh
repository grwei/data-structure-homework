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

int Ackermann(int m, int n);
int AckermannLoop(int m, int n);

static int Akm_deep = 0; // 当前递归深度
static int deep_max = 0; // 最大递归深度
int Ackermann(int m, int n)
{
    static time_t begTime = time(nullptr);

    if (++Akm_deep > deep_max)
    {
        ++deep_max;
        std::cout << "Max deep: " << std::setw(10) << std::left << std::setw(10) << deep_max << "Time(s): " << difftime(time(nullptr), begTime) << '\r';
    }
    // std::cout << "Current deep: " << std::setw(10) << std::left << Akm_deep << " Max deep: " << std::setw(10) << deep_max << '\r';
    // printf("m = %-10.7g n = %-10.7g\r", (float)m, (float)n);
    // std::cout << "m = " << std::setw(10) << std::left << m << "n = " << std::setw(10) << std::left << n << '\r';
    if (!m)
    {
        --Akm_deep;
        return n + 1;
    }
    if (!n)
    {
        --Akm_deep;
        return Ackermann(m - 1, 1);
    }

    int midVal = Ackermann(m, n - 1);

    --Akm_deep;
    return Ackermann(m - 1, midVal);
}

int AckermannLoop(int m, int n)
{
    deep_max = Akm_deep = 0; // 模拟栈深度计数
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
        if ((Akm_deep = SnapShotStack.size()) > deep_max)
        {
            ++deep_max;
            // std::cout << "m = " << std::setw(10) << std::left << currentSnapshot.m << "n = " << std::setw(10) << currentSnapshot.n << " Current deep: " << std::setw(10) << Akm_deep << " Max deep: " << std::setw(10) << deep_max << '\r';
            std::cout << "Max deep: " << std::setw(10) << std::left << std::setw(10) << deep_max << "Stack size(kB): " << std::setw(10) << SnapShotStack.elemMem() / 1024 << "Time(s): " << difftime(time(nullptr), begTime) << '\r';
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

    std::cout << "Current deep: " << std::scientific << std::setw(10) << std::left << std::setw(10) << Akm_deep << " Max deep: " << std::setw(10) << deep_max << "Stack size(kB): " << std::setw(10) << SnapShotStack.elemMem() / 1024;
    std::cout << "\nStack's cleared.\n";
    return retVal;
}

#endif
