#ifndef NIFIXEXPER_TO_POSTEXPER_H
#define NIFIXEXPER_TO_POSTEXPER_H

// 中缀表达式转后缀表达式并求值

#include <iostream>
#include <string>
#include <stack>

namespace NifixExper
{
    using std::cout;
    using std::stack;
    using std::string;
    // 判断是否为操作符
    bool isOperator(char c)
    {
        // 判断是否为操作符
        if (c == '+' || c == '-' || c == '*' || c == '/')
            return true;
        else
            return false;
    }

    // 判断操作符优先级
    int priority(char c)
    {
        // 判断操作符优先级
        if (c == '+' || c == '-')
            return 1;
        else if (c == '*' || c == '/')
            return 2;
        else
            return 0;
    }

    // 判断是否为数字
    bool isNumber(char c)
    {
        // 判断是否为数字
        if (c >= '0' && c <= '9')
            return true;
        else
            return false;
    }

    // 中缀表达式转后缀表达式
    string infixToPostfix(string infix)
    {
        // 创建一个栈，用于存储运算符
        stack<char> stk;
        // 用于存储后缀表达式
        string postfix = "";
        // 用于存储数字
        string number = "";
        // 遍历输入的表达式
        for (int i = 0; i < infix.length(); i++)
        {
            // 判断当前字符是否为数字
            if (isNumber(infix[i]))
            {
                number += infix[i];
            }
            else
            {
                // 如果当前字符为数字，则将其添加到后缀表达式中
                if (!number.empty())
                {
                    postfix += number + " ";
                    number = "";
                }

                // 如果当前字符为左括号，则将其入栈
                if (infix[i] == '(')
                {
                    stk.push(infix[i]);
                }

                // 如果当前字符为右括号，则将栈顶元素弹出直到遇到左括号
                else if (infix[i] == ')')
                {
                    while (stk.top() != '(')
                    {
                        postfix += stk.top();
                        stk.pop();
                    }
                    stk.pop();
                }

                // 如果当前字符为运算符，则将栈顶元素弹出直到遇到空栈或者遇到优先级小于当前运算符的运算符
                else if (isOperator(infix[i]))
                {
                    // 如果栈为空，则将当前运算符入栈
                    if (stk.empty())
                    {
                        stk.push(infix[i]);
                    }
                    else
                    {
                        // 如果栈顶元素优先级小于当前运算符，则将栈顶元素弹出并添加到后缀表达式中，直到栈顶元素优先级大于当前运算符或者栈为空
                        if (priority(infix[i]) > priority(stk.top()))
                        {
                            stk.push(infix[i]);
                        }
                        else
                        {
                            while (!stk.empty() && priority(infix[i]) <= priority(stk.top()))
                            {
                                postfix += stk.top();
                                stk.pop();
                            }
                            stk.push(infix[i]);
                        }
                    }
                }
            }
        }
        // 如果数字不为空，则将其添加到后缀表达式中
        if (!number.empty())
        {
            postfix += number + " ";
        }

        // 将栈中剩余的运算符弹出并添加到后缀表达式中
        while (!stk.empty())
        {
            postfix += stk.top();
            stk.pop();
        }
        return postfix;
    }

    int calculate(const string postfix)
    {
        // 创建一个栈来存储数字
        stack<int> stk;
        // 创建一个字符串来存储数字
        string number = "";
        // 遍历后缀表达式中的每个字符
        for (int i = 0; i < postfix.length(); i++)
        {
            // 检查字符是否为空格
            if (postfix[i] == ' ')
            {
                // 如果数字不为空，将其压入栈中
                if (!number.empty())
                {
                    stk.push(stoi(number));
                    number = "";
                }
            }
            // 检查字符是否为操作符
            else if (isOperator(postfix[i]))
            {
                // 弹出栈顶的两个元素
                int num1 = stk.top();
                stk.pop();
                int num2 = stk.top();
                stk.pop();
                // 检查操作符，并将结果压入栈中
                if (postfix[i] == '+')
                {
                    stk.push(num2 + num1);
                }
                else if (postfix[i] == '-')
                {
                    stk.push(num2 - num1);
                }
                else if (postfix[i] == '*')
                {
                    stk.push(num2 * num1);
                }
                else if (postfix[i] == '/')
                {
                    stk.push(num2 / num1);
                }
            }
            // 如果字符为数字，将其添加到数字字符串中
            else
            {
                number += postfix[i];
            }
        }
        // 返回最终结果
        return stk.top(); // 返回最终结果
    }
}
#endif // NIFIXEXPER_TO_POSTEXPER_H