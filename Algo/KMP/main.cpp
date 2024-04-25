#include "KMP.h"
#include <format>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>
int main()
{

    using namespace std;
    string text = "abcaabbabcabaacbacba";
    cout << "the text is: " << text << "\n";
    map<string, function<vector<int>(const string &)>> m{
        {"findPattern", findPattern},
        {"getNext", getNext},
        {"getNextVal", getNextVal}};
    vector<int> patternArray;
    for (auto fn : m)
    {
        cout << format("the result of {} is: ", fn.first);
        patternArray = move(fn.second(text));
        for (auto elem : patternArray)
            cout << elem << ' ';
        patternArray.clear();
        cout << '\n';
    }
}