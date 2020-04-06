/**
 * @file ch3_4.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Rpn.hh"
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

    try
    {
        // 用户在命令行参数arg1输入中缀式
        if (argc > 1)
        {
            std::cout << "\nInfix: " << argv[1] << '\n';
            std::cout << "Postfix: " << RPN::Rpn_t(argv[1]).postfix() << std::endl;

            t = clock() - t;
            printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
            return 0;
        }

        std::string infixStr1{"(5+6^2*(7+3)/3)/4+5"};
        RPN::Rpn_t rpn{infixStr1, RPN::notationType::Infix};

        std::cout << "\nInfix: " << infixStr1 << '\n';
        std::cout << "Postfix: " << rpn.postfix() << '\n';

        // 用户交互输入中缀式
        char expr[RPN::buf_size];
        do
        {
            std::cout << "Input infix expression: ";
            std::cin.getline(expr, RPN::buf_size, '\n');
            if (!std::cin.fail())
                break;

            std::cin.clear();
            std::cin.sync();
        } while (true);

        std::cout << "\nInfix: " << expr << '\n';
        std::cout << "Postfix: " << rpn.assign(expr).postfix() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    t = clock() - t;
    printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

    return 0;
}
