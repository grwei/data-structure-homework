#include "dLinkList.h"

int main(int argc, char const *argv[])
{
    List::dLinkList<int> listA, listB;

    for (int i = 0; i < 10; ++i)
    {
        listA.insert(i, i + 1);
        listB.insert(i, -i - 1);
    }

    listA.traverse();
    listB.traverse();
    (listA + listB).traverse();

    return 0;
}
