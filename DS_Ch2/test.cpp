#include "List"
#include <iostream>
#include <utility>
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<int> vec_int_1{1, 2, 3, 4, 5};
    std::vector<int> vec_int_2{5, 2, 3, 4, 1};
    std::cout << static_cast<const void *>(&vec_int_1) << '\n';
    std::cout << static_cast<const void *>(&vec_int_2) << '\n';

    auto tmp = std::move(vec_int_1);
    vec_int_1 = std::move(vec_int_2);
    vec_int_2 = std::move(tmp);
    // std::cout << vec_int_2[2];
    std::cout << static_cast<const void *>(&vec_int_1) << '\n';
    std::cout << static_cast<const void *>(&vec_int_2) << '\n';

    return 0;
}
