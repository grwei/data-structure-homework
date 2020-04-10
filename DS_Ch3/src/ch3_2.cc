/**
 * @file ch3_2.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 将十进制非负实数以二进制打印
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Stack.hh"
#include <cmath>
#include <iostream>
#include <string>

/**
 * @brief 将十进制非负整数以其二进制形式打印
 * 
 * @param decUi 非负十进制整数
 */
static void prnUIntInBin(unsigned long decUi = 0);

/**
 * @brief 将（非负）十进制纯小数以其二进制形式打印
 * 
 * @param pDec 十进制纯小数
 * @param errP 允许误差: 2^(-errP), 即输出小数点后errP位。默认取值20
 * 
 */
static void prnPDecInBin(double pDec = 0.0, unsigned int errP = 20);

/**
 * @brief 将非负十进制实数以其二进制形式打印
 * 
 * @param argc 命令行参数的个数
 * @param argv 命令行参数的值
 * @return int 程序正常终止时返回0
 * 
 * @details 可选：命令行arg[1]为一个合法的非负十进制实数。若不给出，程序将要求用户输入。
 * 合法表示: https://en.cppreference.com/w/cpp/language/floating_literal
 */
int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        auto decNum = std::stod(argv[1], 0);
        if (decNum < 0)
            throw(std::string{"argv[1] should be a non-negative decimal number!"});

        auto IntPart = floor(decNum); //整数部分
        prnUIntInBin(IntPart);
        prnPDecInBin(decNum - IntPart);
        std::cout << std::endl;
        return 0;
    }

    double decNum{0.0};

    // Get legal input
    do
    {
        std::cout << "Please input a non-negative decimal number: " << std::endl;
        std::cin >> decNum;
        if (!std::cin.fail() && decNum >= 0)
            break;

        std::cin.clear();
        std::cin.sync();
    } while (true);

    auto IntPart = floor(decNum);
    prnUIntInBin(IntPart);
    prnPDecInBin(decNum - IntPart);
    std::cout << std::endl;

    return 0;
}

void prnUIntInBin(unsigned long decUi)
{
    Stack::linkStack<char> lst{};
    do
    {
        lst.push(decUi % 2 + '0');
        decUi /= 2;
    } while (decUi);

    std::cout << "Binary representation:\n";
    while (!lst.isEmpty())
        std::cout << lst.pop();
}

void prnPDecInBin(double pDec, unsigned int errP)
{
    std::cout << '.';

    if (pDec >= 1)
        throw(std::string{"Not a pure decimal!"});

    do
    {
        pDec *= 2;
        if (pDec >= 1)
        {
            std::cout << '1';
            --pDec;
            --errP;
            continue;
        }
        std::cout << '0';
    } while (errP && pDec);
}
