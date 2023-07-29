#### 3.3.1

>  假设一个算术表达式中包含圆括号、方括号和花括号 $3$种类型的括号，编写一个算法来判别表达式中的括号是否配对，以字符`\0`作为算术表达式的结束符.

```cpp
//参考 栈在括号匹配中的应用.cpp
bool bracketCheck(string str,int len)
{
    SqStack S;
    InitStack(S);

    for(int i=0;i<len;i++)
    {
        if(str[i]=='('||str[i]=='['||str[i]=='{')
            Push(S,str[i]);
        else
        {
            if(StackEmpty(S)==true)//栈空(右括号无匹配)
                return false;
            ElemType x;
            Pop(S,x);

            if(str[i]==')'&&x!='(')//左右括号不匹配
                return false;
            if(str[i]==']'&&x!='[')
                return false;
            if(str[i]=='}'&&x!='{')
                return false;
        }
    }
    return StackEmpty(S);//左括号不匹配
}

if(bracketCheck(s,s.size())==true)
    cout << "匹配成功" << endl;
else cout << "匹配失败" << endl;
```

#### 3.3.2 

>  按下图所示铁道进行车厢调度（注意，两侧铁道均为单向行驶道，火车调度站有一个用于调度的“栈道”)，火车调度站的入口处有 $n$节硬座和软座车厢（分别用 $H$和 $S$表示)等待调度，试编写算法，输出对这 $n$节车厢进行调度的操作（即入栈或出栈操作）序列，以使所有的软座车厢都被调整到硬座车厢之前.
>
> ![](https://cdn.acwing.com/media/article/image/2023/07/29/85276_7e523c622d-20230729154923.png) 

设车道为 $B$,每次将硬座 $H$入栈, 软座 $S$入车道 $B$中,当所有的座位都检查完,将硬座 $H$出栈接在车道 $B$之后,即可实现所有的软座车厢都被调整到硬座车厢之前.

```cpp
string trainArrange(string str,int len)
{
    SqStack S;
    InitStack(S);
    string res="";

    for(int i=0;i<len;i++)
    {
        if(str[i]=='S')//软座
            res+='S';
        else //硬座
            Push(S, str[i]);
    }

    while(StackEmpty(S)==false)//将剩余硬座接在软座之后
    {
        char seat;
        Pop(S, seat);
        res+=seat;
    }
    return res;
}
```

#### 3.3.3

>  利用一个栈实现以下递归函数的非递归计算:
>
> 
>
> ![](https://cdn.acwing.com/media/article/image/2023/07/29/85276_e58c32842d-20230729160458.png) 