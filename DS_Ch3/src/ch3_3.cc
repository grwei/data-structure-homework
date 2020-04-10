/**
 * @file ch3_3.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 全排列的递归和非递归实现
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Permute.hh"

int main(int argc, char const *argv[])
{
    // time
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);                                                 // Get the current calendar time
    timeinfo = localtime(&rawtime);                                 // Convert time_t to tm as local time
    printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert tm structure to string

    clock_t t;

    if (argc > 1)
    {
        // std::cout << "\nNon-recursive permute(STL):\n";
        // ch3_3::permute_stl(std::string(argv[1]));

        std::cout << "Recursive permute:\n";
        t = clock();
        ch3_3::permute_rec(std::string(argv[1]));
        t = clock() - t;
        printf("permute_rec(%s) took %ld clicks (%f seconds).\n", argv[1], t, ((float)t) / CLOCKS_PER_SEC);

        std::cout << "\nNon-recursive permute(Stack):\n";
        t = clock();
        ch3_3::permute_loop(std::string(argv[1]));
        t = clock() - t;
        printf("permute_loop(%s) took %ld clicks (%f seconds).\n", argv[1], t, ((float)t) / CLOCKS_PER_SEC);

        return 0;
    }

    std::string str;
    do
    {
        std::cout << "\nPlease input a string: ";
        std::cin >> str;
        if (!std::cin.fail())
            break;

        std::cin.clear();
        std::cin.sync();
    } while (true);

    std::cout << "\nNon-recursive permute(STL):\n";
    t = clock();
    ch3_3::permute_stl(str);
    t = clock() - t;
    printf("permute_stl(%s) took %ld clicks (%f seconds).\n", str.c_str(), t, ((float)t) / CLOCKS_PER_SEC);

    std::cout << "Recursive permute:\n";
    t = clock();
    ch3_3::permute_rec(str);
    t = clock() - t;
    printf("permute_rec(%s) took %ld clicks (%f seconds).\n", str.c_str(), t, ((float)t) / CLOCKS_PER_SEC);

    std::cout << "\nNon-recursive permute(Stack):\n";
    t = clock();
    ch3_3::permute_loop(str);
    t = clock() - t;
    printf("permute_loop(%s) took %ld clicks (%f seconds).\n", str.c_str(), t, ((float)t) / CLOCKS_PER_SEC);

    return 0;
}
