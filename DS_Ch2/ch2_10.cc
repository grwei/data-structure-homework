#include "sLinkList.h"

int main(int argc, char const *argv[])
{
    const List::sLinkList<char> wdA{'l', 'o', 'a', 'd', 'i', 'n', 'g'};
    List::sLinkList<char> wdB{'b', 'e', 'i', 'n', 'g'};

    wdA.traverse();
    wdB.traverse();

    List::sLinkList<char>::const_iterator str1 = wdA.begin(); // const_iterator
    auto str2 = wdB.begin();                                  // iterator

    int len1 = wdA.length();
    auto len2 = wdB.length();

    // 尾部对齐
    if (len1 > len2)
        for (int i = 0; i < len1 - len2; ++i)
            ++str1;
    else
        for (int i = 0; i < len2 - len1; ++i)
            ++str2;

    while (!str1.isEnd() && !str2.isEnd())
    {
        // 跳过不相同的字符
        while (!str1.isEnd() && !str2.isEnd() && *str1 != *str2)
        {
            ++str1;
            ++str2;
        }

        if (str1.isEnd())
        {
            std::cout << "\nNo suffix" << std::endl;
            return 0;
        }

        // 判定是否尾缀：跳过相同字符
        auto tmp1 = str1;
        auto tmp2 = str2;
        while (!tmp1.isEnd() && !tmp2.isEnd() && *tmp1 == *tmp2)
        {
            ++tmp1;
            ++tmp2;
        }

        if (tmp1.isEnd()) // 是后缀
        {
            std::cout << "\nSuffix found:\n";
            while (!str1.isEnd())
                std::cout << *str1++;
            std::cout << std::endl;
            break;
        }

        // 不是后缀，从下一位置再次试验
        str1 = ++tmp1;
        str2 = ++tmp2;
    }

    return 0;
}
