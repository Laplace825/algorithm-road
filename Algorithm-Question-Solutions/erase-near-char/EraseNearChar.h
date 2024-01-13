#ifndef ERASE_NEAR_CHAR_H
#define ERASE_NEAR_CHAR_H

#include <string>
#include <stack>

// 实现一个函数
// 删除所有相邻的两个相同字符
// 比如 abbaca 删除后只剩下ca
// 使用栈来完成

std::string eraseNearChar(const std::string &str)
{
    std::string ans;
    for (char c : str)
    {
        if (ans.empty() || ans.back() != c)
        {
            ans.push_back(c);
        }
        else
        {
            ans.pop_back();
        }
    }
    return ans;
}

#endif // ERASE_NEAR_CHAR_H