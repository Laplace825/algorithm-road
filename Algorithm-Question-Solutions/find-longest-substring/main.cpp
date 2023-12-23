
#include "FindLongSubStr.h"
#include <string>
using std::string;
using std::cout ;

int main(int argc , char **argv)
{
    string s1 = "abaac";
    string s2 = "avbaacss";
    string s3 = longestCommonSubstring(s1 ,s2);
    cout << s3 << '\n';
}