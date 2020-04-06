#include <iostream>

long long calcSum(long long n);
int main(int argc, char const *argv[])
{
    long long n{0};

    std::cout << "Please input a positive integer: ";
    do
    {
        std::cin >> n;
        // check if input is legal
        if (std::cin.fail() || n <= 0)
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

long long calcSum(long long n)
{
    if(n % 2 == 0)
        return -n / 2;
    return (n + 1) / 2;
}
