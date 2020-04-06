#include "seqList.h"

int main(int argc, char const *argv[])
{
    List::seqList<int> listA{10}, listB{10};

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
