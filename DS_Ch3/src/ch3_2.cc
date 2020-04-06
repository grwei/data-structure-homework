/**
 * @file ch3_2.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Stack.hh"
#include <iostream>
#include <string>

void prnNonNegDecInBin(unsigned long dec = 0);

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        prnNonNegDecInBin(std::stoul(argv[1], 0, 10));
        return 0;
    }

    unsigned long dec{0};

    // Get legal input
    do
    {
        std::cout << "Please input a non-negative decimal integer: " << std::endl;
        std::cin >> dec;
        if (!std::cin.fail())
            break;

        std::cin.clear();
        std::cin.sync();
    } while (true);

    prnNonNegDecInBin(dec);

    return 0;
}

void prnNonNegDecInBin(unsigned long dec)
{
    Stack::linkStack<char> lst{};
    do
    {
        lst.push(dec % 2 + '0');
        dec /= 2;
    } while (dec);

    std::cout << "Binary representation:\n";
    while (!lst.isEmpty())
        std::cout << lst.pop();

    std::cout << std::endl;
}
