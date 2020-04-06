#include <iostream>

bool isPrime(long long n);
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

    std::cout << "\nn is" << ((isPrime(n)) ? " a " : " not a ") << "prime." << std::endl;

    return 0;
}

bool isPrime(long long n)
{
    if (n <= 1)
        return false;
    
    for (int i = 2; i * i <= n; ++i)
        if(n % i == 0)
            return false;

    return true;
}

