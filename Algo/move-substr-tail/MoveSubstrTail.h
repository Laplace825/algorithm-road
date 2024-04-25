#ifndef MOVE_SUBSTR_TAIL_H
#define MOVE_SUBSTR_TAIL_H

#include <string>
#include <cstring>

/**
 * @note: str 长度为S, index 为移动的起点, len 为移动的长度
 **/

void MoveSubstrTail(std::string &str, int index, int len)
{
    using std::string;
    string tmp = str.substr(index, len);
    str.erase(index, len);
    str += tmp;
}

/**
 * @note: arr 下标从1开始, 长度为S, index 为移动的起点, len 为移动的长度
 **/

void MoveSubstrTailArr(char *arr, int index, int len)
{
    int arrLength = strlen(arr);
    char *tmp = new char[len + 1];
    memcpy(tmp, arr + index, len + 1);
    memmove(arr + index, arr + index + len, arrLength - (index + len) + 1);
    memcpy(arr + arrLength - len, tmp, len);
    delete[] tmp;
    tmp = nullptr;
}

#endif // MOVE_SUBSTR_TAIL_H