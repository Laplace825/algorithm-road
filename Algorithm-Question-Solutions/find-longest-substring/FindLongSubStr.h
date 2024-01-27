#ifndef FIND_LONG_SUB_STR_H
#define FIND_LONG_SUB_STR_H

#include <iostream>
#include <string>
#include <vector>

std::string longestCommonSubstring(const std::string &s1, const std::string &s2)
{
    // 初始化长度
    int n = s1.size();
    int m = s2.size();

    // dp
    // 初始化dp数组，dp[i][j]表示s1[0:i-1]和s2[0:j-1]的最长公共子串长度
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    // 初始化最大长度和结束位置
    int maxLen = 0, endIndex = 0;
    // O(m*n)
    std::cout << "  ";
    for (auto ch : s2)
    {
        std::cout << ch << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < n; i++)
    {
        std::cout << s1[i] << ' ';
        for (int j = 0; j < m; j++)
        {
            // 如果当前字符相等
            if (s1[i] == s2[j])
            {
                // dp[i+1][j+1]表示s1[0:i]和s2[0:j]的最长公共子串长度
                dp[i + 1][j + 1] = 1 + dp[i][j];
                // 如果当前长度大于最大长度，更新最大长度和结束位置
                if (dp[i + 1][j + 1] > maxLen)
                {
                    maxLen = dp[i + 1][j + 1];
                    endIndex = i;
                }
            }
            std::cout << dp[i + 1][j + 1] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "endIndex:" << endIndex << '\n';
    // 返回最大长度对应的子串
    return s1.substr(endIndex - maxLen + 1, maxLen);
}

#include "KMP.h"

std::string KMPversion(const std::string &s1, const std::string &s2)
{
    // O(n^3) 不推荐
    int patterIndex = 0, maxLen = 0;
    int matchIndex = 0;
    size_t loopLen = 0;
    std::string biggerStr;
    std::string smallerStr;
    // 用更长的字符串做查找的母串
    if (s1.size() > s2.size())
    {
        loopLen = s2.size();
        biggerStr = s1;
        smallerStr = s2;
    }
    else
    {
        loopLen = s1.size();
        biggerStr = s2;
        smallerStr = s1;
    }
    for (int j = 0; j < loopLen; j++)
    {
        for (int len = 1; len <= loopLen - j; len++)
        {
            patterIndex = KMP(biggerStr, smallerStr.substr(j, len));
            if (patterIndex != -1)
            {
                // 如果直接用 endIndex != -1 && maxLen < len会导致错误触发else break
                if (maxLen < len)
                {
                    matchIndex = patterIndex;
                    maxLen = len;
                }
            }
            else
                break;
        }
    }
    return biggerStr.substr(matchIndex, maxLen);
}

#endif // FIND_LONG_SUB_STR_H