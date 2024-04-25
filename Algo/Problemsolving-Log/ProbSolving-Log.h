#ifndef PROB_SOLVING_LOG_H
#define PROB_SOLVING_LOG_H
#include <vector>
#include <string>
#include <iostream>

void probSolvingLog()
{
    using std::cin, std::cout;
    using std::string;
    using std::vector;
    vector<char> hashTable(300);
    for (int i = 0; i < 26; i++)
    {
        hashTable.at('A' + i) = i + 1;
    }
    long long n; // n is the number of the test cases
    cin >> n;
    string str; // str is the string

    long long timeCount = 0;
    long long time = 0, ans = 0;
    for (auto i = 0; i < n; i++)
    {
        ans = 0;
        cin >> time;
        cin >> str;
        for (auto ch : str)
        {
            if (timeCount < time)
            {
                timeCount += hashTable.at(ch);
                ans++;
            }
            else
                break;
        }
        cout << ans << '\n';
    }
}
#endif // PROB_SOLVING_LOG_H