#ifndef KMP_H
#define KMP_H

#include <array>
#include <string>

// find the pattern array
// the patternArray is just prefix table
std::array<int, 256> findPattern(const std::string& pattern) {
    std::array<int, 256> patternArray{};
    patternArray[0] = 0;
    int prefix_len = 0;
    // an idea like DP
    for( int i=1; i<pattern.length() ;)
    {
        if( pattern[i] == pattern[prefix_len]){
            // if continous match,
            // prefix_len ++ in the base of last prefix_len
            prefix_len++;
            patternArray.at(i++) = prefix_len;
        }   
        else if( prefix_len == 0 ){
            patternArray.at(i++) = 0;
        }
        else{
            // if match failed,
            // return to the last prefix_len,
            // and try to find the next prefix_len
            prefix_len = patternArray.at(prefix_len-1);
            // still I can't understand this step...
        }
    }
    return patternArray;
}

int KMP(const std::string& text, const std::string& pattern) {
    std::array<int, 256> patternArray = findPattern(pattern);
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
              //skip the prefix
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

#endif // KMP_H