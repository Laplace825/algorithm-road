
#include "FindLongSubStr.h"
#include <string>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::string;
    string s1 = "abcdefg";
    string s2 = "abcjdgsgafas";
    string s3 = longestCommonSubstring(s1, s2);
    // string s3 = KMPversion(s1,s2);
    cout << s3 << '\n';
}