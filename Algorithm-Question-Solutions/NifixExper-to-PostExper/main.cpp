#include "NifixExperToPostExper.h"

int main()
{
    // 生成测试
    using std::cout;
    using std::string;
    string infix = "(1+2)*3-10/5";
    string postfix = NifixExper::infixToPostfix(infix);
    cout << "中缀表达式：" << infix << '\n';
    cout << "后缀表达式：" << postfix << '\n';
    cout << "求值：" << NifixExper::calculate(postfix) << '\n';
    return 0;
}