/**
 * @file test.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>

int main(int argc, char const *argv[])
{
    int i = 0;
    while (i < 0xFFFF)
    {
        std::cout << "Line " << i++;
        std::cout << '\r';
    }
    return 0;
}
