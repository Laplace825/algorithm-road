#include "KMP.h"
#include <format>
#include <bits/stdc++.h>

using fnPtr = std::vector<int> (* [3])(const std::string &); 

int main(int argc, char** argv) {
    
    using namespace std;
    string text = "abcaabbabcabaacbacba";
    fnPtr fnArr = {findPattern , getNext , getNextVal};
    vector<int> patternArray;
    for(auto fn: fnArr){
        patternArray = fn(text);
        for(auto elem : patternArray)
            cout << elem << ' ';
        patternArray.clear();
        cout << '\n';
    }
}