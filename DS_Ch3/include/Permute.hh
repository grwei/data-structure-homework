/**
 * @file Permute.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 全排列
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __PERMUTE_HH__
#define __PERMUTE_HH__

#include "Stack.hh"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>

namespace ch3_3
{
// 工具: 交换
// 参考: http://www.cplusplus.com/reference/algorithm/swap/
template <class T>
void swap(T &a, T &b)
{
    T c(std::move(a));
    a = std::move(b);
    b = std::move(c);
}

// 工具: 逆序[first, last)
// 参考: https://en.cppreference.com/w/cpp/algorithm/reverse
template <class BidirIt>
void reverse(BidirIt first, BidirIt last)
{
    while ((first != last) && (first != --last))
        swap(*first++, *last);
}

// 工具: 递归输出固定前缀[first, fixPos)的[first, last)的全排列. fixPos为first表示不固定任何元素.
// 参考: https://leetcode-cn.com/problems/permutations-ii/
template <class BidirIt>
void permuteWithFixedPrefix(BidirIt first, BidirIt last, BidirIt fixPos)
{
    /* BEGIN: stage-0 */
    if (fixPos == last)
    {
        for (BidirIt i = first; i != last; ++i)
            std::cout << *i;
        std::cout << std::endl;
        return; // GOTO: return
    }
    /* END: stage-0 */ // PUSH: stage-1

    // 任务: 输出固定前缀[first, fixPos)的全排列. 可分解为:
    // 令[fixPos, last)间各数依次占据fixPos位, 然后输出固定前缀[first, fixPos]的全排列.
    for (BidirIt i1 = fixPos; i1 != last; ++i1)
    {
        /* BEGIN: stage-1 */
        // 判断是否重复分支:
        // 若i1所指已在[fixPos, i1)中出现, 则此分支为重复
        bool isRep = false;
        for (BidirIt i2 = fixPos; i2 < i1; ++i2)
        {
            if (*i1 == *i2)
            {
                isRep = true;
                break;
            }
        }
        if (isRep) // 跳过重复分支 // PUSH: stage-1, then return
            continue;

        swap(*i1, *fixPos);

        BidirIt i = fixPos;
        /* END: stage-1 */ // PUSH stage-2
        permuteWithFixedPrefix(first, last, ++i);

        /* BEGIN: stage-2 */
        swap(*i1, *fixPos);
        // ++i1;
        /* END: stage-2 */ // PUSH: stage-1
    }
}

// 工具: 栈模拟的递归输出固定前缀[first, fixPos)的[first, last)的全排列. fixPos为first表示不固定任何元素.
// 参考: https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
template <class BidirIt>
void permuteWithFixedPrefix_Loop(BidirIt first, BidirIt last, BidirIt fixPos)
{
    struct SnapShotStruct
    {
        BidirIt first; // - parameter input
        BidirIt last;
        BidirIt fixPos;
        BidirIt i1; // for-loop
        int stage;
    };

    Stack::linkStack<SnapShotStruct> snapshotStack;
    SnapShotStruct currentSnapshot;
    currentSnapshot.first = first;
    currentSnapshot.fixPos = fixPos;
    currentSnapshot.last = last;
    currentSnapshot.i1 = fixPos;
    currentSnapshot.stage = 0;
    snapshotStack.push(currentSnapshot);

    while (!snapshotStack.isEmpty())
    {
        currentSnapshot = snapshotStack.top();
        snapshotStack.pop();

        switch (currentSnapshot.stage)
        {
        case 0:
        {
            if (currentSnapshot.fixPos == currentSnapshot.last)
            {
                for (BidirIt i = currentSnapshot.first; i != currentSnapshot.last; ++i)
                    std::cout << *i;
                std::cout << std::endl;

                continue;
            }

            currentSnapshot.stage = 1;
            snapshotStack.push(currentSnapshot);
            continue;
            break;
        }
        case 1:
        {
            if (currentSnapshot.i1 == currentSnapshot.last)
                continue;

            bool isRep = false;
            for (BidirIt i2 = currentSnapshot.fixPos; i2 < currentSnapshot.i1; ++i2)
            {
                if (*currentSnapshot.i1 == *i2)
                {
                    isRep = true;
                    break;
                }
            }
            if (isRep) // 跳过重复分支
            {
                ++currentSnapshot.i1;
                currentSnapshot.stage = 1;
                snapshotStack.push(currentSnapshot);
                continue;
            }

            swap(*currentSnapshot.i1, *currentSnapshot.fixPos);

            currentSnapshot.stage = 2;
            snapshotStack.push(currentSnapshot);

            // new call
            currentSnapshot.i1 = ++currentSnapshot.fixPos;
            currentSnapshot.stage = 0;
            snapshotStack.push(currentSnapshot);
            continue;
            break;
        }
        case 2:
        {
            swap(*currentSnapshot.i1, *currentSnapshot.fixPos);

            ++currentSnapshot.i1;
            currentSnapshot.stage = 1;
            snapshotStack.push(currentSnapshot);
            continue;
            break;
        }
        }
    }
}

// 递归输出_s的全排列
template <class T>
void permute_rec(const T &_s)
{
    if (_s.empty())
        throw(std::string{"Empty container!\n"});
    T s = _s;

    permuteWithFixedPrefix(s.begin(), s.end(), s.begin());
}

// 栈模拟的递归输出_s的全排列
template <class T>
void permute_loop(const T &_s)
{
    if (_s.empty())
        throw(std::string{"Empty container!\n"});
    T s = _s;

    permuteWithFixedPrefix_Loop(s.begin(), s.end(), s.begin());
}

// 工具: 非递归地使序列变为下一排序[first, last)
// 参考: https://en.cppreference.com/w/cpp/algorithm/next_permutation
template <class BidirIt>
bool next_perm(BidirIt first, BidirIt last)
{
    if (first == last) // 若序列为空, 结束.
        return false;
    BidirIt i = last;
    if (first == --i) // 令i指向最后一个元素. 若序列仅含一个元素, 结束.
        return false;

    while (true)
    {
        BidirIt i1, i2;

        i1 = i;
        if (*--i < *i1) // 若已从低位向高位找到了首个逆序（高位小于低位）. 此时i和i1指向这对逆序
        {
            i2 = last;
            while (!(*i < *--i2)) // 令i2指向从低位向高位首个大于*i的数
                ;
            swap(*i, *i2);
            ch3_3::reverse(i1, last);
            return true;
        }
        if (i == first) // 若序列已是顺序的（从高位向低位为非增）, 则不存在更大的排序, 结束.
        {
            ch3_3::reverse(first, last); // 当前排序是最大排序, 逆置后成为最小排序
            return false;
        }
    }
}

// 非递归输出_s的全排列
template <class T>
void permute_stl(const T &_s)
{
    T s = _s;
    std::sort(s.begin(), s.end());

    do
    {
        std::cout << s << '\n';
    } while (next_perm(s.begin(), s.end()));
}

} // namespace ch3_3

#endif
