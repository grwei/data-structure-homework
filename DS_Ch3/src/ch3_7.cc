/**
 * @file ch3_7.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Ackermann.hh"

int main(int argc, char const *argv[])
{
    // Configure
    bool recEn = true, stkEn = true;
    int x, y;

    // time
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);                                                 // Get the current calendar time
    timeinfo = localtime(&rawtime);                                 // Convert time_t to tm as local time
    printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string

    if (argc > 3)
    {
        if (!strcmp("-s", argv[3])) // 用户指定用堆栈
            recEn = false;

        if (!strcmp("-r", argv[3])) // 用户指定用系统栈
            stkEn = false;
    }

    if (argc > 2)
    {
        x = atoi(argv[1]);
        y = atoi(argv[2]);

        if (stkEn)
            Akm_t::Akm_loop(x, y);

        if (recEn)
            Akm_t::Akm_rec(x, y);

        return 0;
    }

    do
    {
        std::cout << "\nInput [m n]: ";
        std::cin >> x >> y;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.sync();
            continue;
        }

        break;
    } while (true);

    if (stkEn)
        Akm_t::Akm_loop(x, y);

    if (recEn)
        Akm_t::Akm_rec(x, y);

    return 0;
}
