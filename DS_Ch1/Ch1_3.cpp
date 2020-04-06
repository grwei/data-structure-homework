#include <iostream>

long long calcSum(int n);
int main(int argc, char const *argv[])
{
    int n{0};

    std::cout << "Please input a positive integer: ";
    do
    {
        std::cin >> n;
        // check if input is legal
        if (std::cin.fail() || n < 1)
        {
            std::cout << "Please input a positive integer: ";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        // Have got legal input
        std::cin.sync();
        break;
    } while (true);

    std::cout << "\nS = " << calcSum(n) << std::endl;

    return 0;
}

long long calcSum(int n)
{
    long long thisTerm{1}, sum{0};

    for (int i = 1; i <= n; ++i)
        sum += (thisTerm *= i);

    return sum;
}
