#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

    // 找到前缀表
std::vector<int> findPattern(const std::string& pattern) {
    std::vector<int> patternArray(pattern.size() , 0);
    patternArray[0] = 0;
    int prefix_len = 0;
    // 一种类似动态规划的办法
    for( int i=1; i<pattern.length() ;)
    {
        if( pattern[i] == pattern[prefix_len]){
            // 如果持续匹配,
            // prefix_len 在上一次的基础上自增
            patternArray.at(i++) = ++prefix_len;
        }   
        else if( prefix_len == 0 ){
            patternArray.at(i++) = 0;
        }
        else{
            // 匹配失败,
            // prefix_len 返回上一次匹配值,
            // 并继续尝试匹配
            prefix_len = patternArray.at(prefix_len-1);
        }
    }
    return patternArray;
}

int KMP(const std::string& text, const std::string& pattern) {
    std::vector<int> patternArray = findPattern(pattern);
    int i = 0;
    int j = 0;
    while( i < text.length() && j < pattern.length() ){
        if( text[i] == pattern[j] ){
            i++;
            j++;
        }
        else if( j == 0 ){
            i++;
        }
        else{ // text[i]!=pattern[j] 
              // 跳过前缀表中指明的位置
            j = patternArray.at(j-1);
        }
    }
    if( j == pattern.length() ){
        return i - j;
    }
    else{
        return -1;
    }
}


std::vector<int> getNext(const std::string & str)
{
    std::vector<int> next(str.size(), 0);
    next[0] = -1;
    // prefix_len 代表前后缀匹配的长度
    for(int i=0, prefix_len=-1; i<str.size()-1; )
    {
        // prefix_len == -1 意味着匹配长度为空(0)
        if(prefix_len==-1 || str[i]==str[prefix_len])
        {
            next[++i] = ++prefix_len;
        }
        else
        {
            prefix_len = next[prefix_len];
        }
    }
    return next;
}

// 改进的版本

std::vector<int> getNextVal(const std::string & str)
{
    std::vector<int> nextVal(str.size(), 0);
    nextVal[0] = -1;
    auto i = 0, prefix_len = -1;
    auto tmp = 0;
    // prefix_len 代表前后缀已匹配的长度
    while( i < str.size()-1 )
    {
        // prefix_len == -1 意味着前后缀匹配为空(无匹配)
        if(prefix_len==-1 || str[i]==str[prefix_len])
        {
            nextVal[++i] = ++prefix_len;
            
            /* 
            tmp 向前迭代,模拟 str[i] 位置不匹配时 
            str 滑动 next[i] 个位置后的匹配情况
            如果 str[i] != str[tmp],则表明此位置可能与母串可以匹配,将 next[i] 更新为该位置
            */
            tmp = i;
            while(tmp >= 0 && str[i] == str[tmp])
            {
                tmp = nextVal[tmp];
            }
            nextVal[i] = tmp;
        }
        else
        {
            prefix_len = nextVal[prefix_len];
        }
    }
    return nextVal;
}

#endif // KMP_H