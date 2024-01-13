
#include "FindLongSubStr.h"
#include <string>

int main(int argc, char **argv)
{
    using std::cout;
    using std::string;
    string s1 = "abaac";
    string s2 = "avbaacss";
    string s3 = longestCommonSubstring(s1, s2);
    cout << s3 << '\n';
}