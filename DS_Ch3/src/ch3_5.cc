/**
 * @file ch3_5.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 后缀表达式的计算
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Rpn.hh"
#include <cstring>
#include <ctime>

int main(int argc, char const *argv[])
{
    // time
    clock_t t = clock();
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);                                                 // Get the current calendar time
    timeinfo = localtime(&rawtime);                                 // Convert time_t to tm as local time
    printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string

    // configure: 命令行输入arg2为-p, 表示arg1为RPN
    bool isPostExpr = (argc > 2 && !strcmp(argv[2], "-p"));

    try
    {
        if (argc > 1)
        {
            if (isPostExpr) // 用户输入后缀式
            {
                RPN::Rpn_t rpn(argv[1], RPN::notationType::Postfix);
                std::cout << "Postfix: " << rpn.postfix() << '\n';
                std::cout << "Result: " << rpn.calcVal() << std::endl;
                return 0;
            }

            // 若用户输入中缀式
            // 先转为后缀式string
            std::string _postfix = RPN::Rpn_t(argv[1]).postfix();
            std::cout << "Postfix: " << _postfix << '\n';

            // 用后缀string构造新对象, 并求值
            std::cout << "Result: " << RPN::Rpn_t(_postfix, RPN::notationType::Postfix).calcVal() << std::endl;

            t = clock() - t;
            printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
            return 0;
        }

        std::string infixStr1{"(5+6^2*(7+3)/3)/4+5"};
        std::cout << "\nInfix: " << infixStr1 << '\n';

        RPN::Rpn_t rpn(infixStr1);                             // 用中缀string构造对象
        std::cout << "Postfix: " << rpn.postfix() << '\n';     // 输出转换得到的后缀string
        rpn.assign(rpn.postfix(), RPN::notationType::Postfix); // 用后缀string修改对象
        std::cout << "Result: " << rpn.calcVal() << std::endl; // 输出表达式的值

        // 用户交互地输入后缀式
        char expr[RPN::buf_size];
        do
        {
            std::cout << "Input postfix notation: ";
            std::cin.getline(expr, RPN::buf_size, '\n');
            if (!std::cin.fail())
                break;

            std::cin.clear();
            std::cin.sync();
        } while (true);

        std::cout << "\nPostfix: " << expr << '\n';
        std::cout << "Result: " << rpn.assign(expr, RPN::notationType::Postfix).calcVal() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    t = clock() - t;
    printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

    return 0;
}
