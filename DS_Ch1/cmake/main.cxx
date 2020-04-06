#include "func.h"
#include "mainConfig.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << main_VERSION_MAJOR << "."
                  << main_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }
    std::cout << "Here is main.n";
    std::cout << fun1() << fun2() << fun3() << std::endl;

    return 0;
}
