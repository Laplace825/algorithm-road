#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

// 找到前缀表
std::vector<int> findPattern(const std::string &pattern)
{
    std::vector<int> patternArray(pattern.size(), 0);
    patternArray[0] = 0;
    int prefix_len = 0;
    // 一种类似动态规划的办法
    for (int i = 1; i < pattern.length();)
    {
        if (pattern[i] == pattern[prefix_len])
        {
            // 如果持续匹配,
            // prefix_len 在上一次的基础上自增
            patternArray.at(i++) = ++prefix_len;
        }
        else if (prefix_len == 0)
        {
            patternArray.at(i++) = 0;
        }
        else
        {
            // 匹配失败,
            // prefix_len 返回上一次匹配值,
            // 并继续尝试匹配
            prefix_len = patternArray.at(prefix_len - 1);
        }
    }
    return patternArray;
}

int KMP(const std::string &text, const std::string &pattern)
{
    std::vector<int> patternArray = findPattern(pattern);
    int i = 0;
    int j = 0;
    while (i < text.length() && j < pattern.length())
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if (j == 0)
        {
            i++;
        }
        else
        { // text[i]!=pattern[j]
          // 跳过前缀表中指明的位置
            j = patternArray.at(j - 1);
        }
    }
    if (j == pattern.length())
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

std::vector<int> getNext(const std::string &str)
{
    /**
     * @return: next数组存放失效函数值
     **/
    std::vector<int> next(str.size(), 0);
    next[0] = -1;
    int i = 0, prefix_len = -1;
    // prefix_len 代表前后缀匹配的长度
    while (i < str.size() - 1)
    {
        // prefix_len == -1 意味着匹配长度为空(0)
        if (prefix_len == -1 || str[i] == str[prefix_len])
            next[++i] = ++prefix_len;
        else
            prefix_len = next[prefix_len];
    }
    return next;
}

// 改进的版本

std::vector<int> getNextVal(const std::string &str)
{
    /**
     * @return: nextVal为改进版本的next数组
     **/
    std::vector<int> nextVal(str.size(), 0);
    nextVal[0] = -1;
    auto i = 0, prefix_len = -1;
    while (i < str.size() - 1)
    {
        // prefix_len == -1 意味着前后缀匹配为空(无匹配)
        if (prefix_len == -1 || str[i] == str[prefix_len])
        {
            ++i;
            ++prefix_len;
            /**
             * @note: 继续模拟匹配,当相同时, prefix_len 所指字符和 i 所指字符完全一样
             * KMP 与母串匹配时跳过子串的位置后,prefix_len 对应位置和母串肯定也不匹配
             * 故当nextVal[i] == nextVal[prefix_len] 时直接等于前缀的nextVal[prefix_len]
             **/
            if (str[i] != str[prefix_len])
                nextVal[i] = prefix_len;
            else
                nextVal[i] = nextVal[prefix_len];
        }
        else
            prefix_len = nextVal[prefix_len];
    }
    return nextVal;
}

#endif // KMP_H