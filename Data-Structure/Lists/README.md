# 第五章

### 何勇乐 22121639

#### 3. 令 S = "abcaabbabcabaacbacba", 分别求出其失效函数值和改进后的失效函数值

| S | a | b | c | a | a | b | b | a | b | c | a | b | a | a | c | b | a | c | b | a |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| *j* | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
| 失效 | -1 | 0 | 0 | 0 | 1 | 1 | 2 | 0 | 1 | 2 | 3 | 4 | 2 | 1 | 1 | 0 | 0 | 1 | 0 | 0 |
| 改进 | -1 | 0 | 0 | -1 | 1 | 0 | 2 | -1 | 0 | 0 | -1 | 4 | 2 | 1 | 1 | 0 | -1 | 1 | 0 | -1 |

```cpp
std::vector<int> getNext(const std::string &str)
{
    /**
     * @return: next数组存放失效函数值
     **/
    std::vector<int> next(str.size(), 0);
    next[0] = -1;
    int i = 0, prefix_len = -1;
    // prefix_len 代表前后缀匹配的长度
    while (i < str.size() - 1)
    {
        // prefix_len == -1 意味着匹配长度为空(0)
        if (prefix_len == -1 || str[i] == str[prefix_len])
            next[++i] = ++prefix_len;
        else
            prefix_len = next[prefix_len];
    }
    return next;
}

// 改进的版本
std::vector<int> getNextVal(const std::string &str)
{
    /**
     * @return: nextVal为改进版本的next数组
     **/
    std::vector<int> nextVal(str.size(), 0);
    nextVal[0] = -1;
    auto i = 0, prefix_len = -1;
    while (i < str.size() - 1)
    {
        // prefix_len == -1 意味着前后缀匹配为空(无匹配)
        if (prefix_len == -1 || str[i] == str[prefix_len])
        {
            ++i;
            ++prefix_len;
            /**
             * @note: 继续模拟匹配,当相同时, prefix_len 所指字符和 i 所指字符完全一样
             * KMP 与母串匹配时跳过子串的位置后,prefix_len 对应位置和母串肯定也不匹配
             * 故当nextVal[i] == nextVal[prefix_len] 时直接等于前缀的nextVal[prefix_len]
             **/
            if (str[i] != str[prefix_len])
                nextVal[i] = prefix_len;
            else
                nextVal[i] = nextVal[prefix_len];
        }
        else
            prefix_len = nextVal[prefix_len];
    }
    return nextVal;
}
```



#### 8.根据前面介绍的广义链表，画出下列广义表的存储表示

将广义链表的一个结点`Node`定义为下表

| Node                                                         |
| :----------------------------------------------------------- |
| `tag`:枚举`enum` ,`HEAD`表示表头,`ATOM`表示该结点是`data`域、`LIST`表示有子表`hlink` |
| `ref`/`data`/`hlink`: 联合体`union`，分别可能为被引用次数 / 数据域 / 子表 |
| `tlink`: 尾                                                  |

![image-20231230120549808](C:\Users\何同学\AppData\Roaming\Typora\typora-user-images\image-20231230120549808.png)

1. $A = ((c),(e),(a,(b,c,d)))$ 
2. $B = ((B,a,(b)),(B))$

上述 A、B 两广义表表示如下图

![Lists](Lists.png)

#### 9.根据前面介绍的 n 元多项式链表的存储结构，画出三元多项式$P(x,y,z)$的存储结构图

原题多项式为 $P(x,y,z) = 2x^7y^3z^2+x5y^4z^2+6x^3y^5z+3xyz+10$ ，这里第二项$x5y^4z^2$中的5不清楚是做系数还是$x$的指数，以下给出两种情况。

| Node                                                         |
| :----------------- |
| `tag`:枚举`enum` ,`var`表示变量,`ptr`表示系数为子多项式、`num`表示系数为一个 |
| `nodename`: 联合体`union`,`vble`表示变量名,`hlink`表示子多项式指针,`coef`表示系数 |
| `exp`: 表示指数大小                                          |
| `tlink`: 尾                                                  |

![image-20231230132525003](C:\Users\何同学\AppData\Roaming\Typora\typora-user-images\image-20231230132525003.png)

#### 5做系数,$5x$

![](.\Lists9.svg)

#### 5做$x$的指数,$x^5$

![Lists92](.\Lists92.svg)