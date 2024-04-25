
#include "FindLongSubStr.h"
#include <string>
#include <format>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::string;
    string s1 = "abcdefg";
    string s2 = "abcjdgsgafas";
    cout << std::format("tow strings are : s1{} s2{}\n", s1, s2);
    string s3 = longestCommonSubstring(s1, s2);
    // string s3 = KMPversion(s1,s2);
    cout << "the lonest common substring : " << s3 << '\n';
}