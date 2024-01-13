#ifndef FIND_LONG_SUB_STR_H
#define FIND_LONG_SUB_STR_H

#include <iostream>
#include <string>
#include <vector>

std::string longestCommonSubstring(std::string s1, std::string s2)
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
  for (int i = 0; i < n; i++)
  {
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
          endIndex = i + 1;
        }
      }
    }
  }

  // 返回最大长度对应的子串
  return s1.substr(endIndex - maxLen, maxLen);
}

#endif // FIND_LONG_SUB_STR_H