#include "sLinkList.h"

int main(int argc, char const *argv[])
{
    List::sLinkList<int> listA{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    listA.traverse();
    listA.findKthLast(3);

    // 测试：返回私有内嵌类的引用，以破坏类的封装性
    auto &ret = listA.retNode();
    auto &pNode = *(ret.next);
    pNode.data = 5;
    listA.traverse();

    return 0;
}
