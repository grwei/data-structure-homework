#include "sLinkList.h"

int main(int argc, char const *argv[])
{
    List::sLinkList<int> slList{};

    for (int i = 0; i < 10; ++i)
        slList.insert(i, i + 1);

    slList.traverse();
    slList.reverse();
    slList.traverse();

    return 0;
}
