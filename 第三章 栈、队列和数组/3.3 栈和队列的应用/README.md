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

已知

*  $P_0(x)=1$;
*  $P_1(x)=2x$;
*  $P_2(x)=2xP_1(x)-2\times 1 P_0(x)$;
*  $P_3(x)=2xP_2(x)-2\times 2 P_1(x)$;
*  $\cdots$;
*  $P_{n-1}(x)=2xP_{n-2}(x)-2\times (n-2) P_{n-3}(x)$;
*  $P_n(x)=2xP_{n-1}(x)-2\times (n-1) P_{n-2}(x)$.

若要求出 $P_n(x)$,需求出 $P_{n-1}(x),P_{n-2}(x),\cdots ,P_1(x),P_0(x)$.

设 $num0=P_0(x)$, $num1=P_1(x)$,此时 $P_2(x)=2x \times num1 - 2\times num0$;

同理若想求出 $P_3(x)$,此时让 $num0=num1$, $num1=P_2(x)$.

最终求出 $P_n(x)$后, $num1$为最终的答案.

不用像书上那样存入`结构体`中,只用记录其对应的下标 $id$即可.

```cpp
int P(int n,int x)
{
    if(n==0)
        return 1;
    
    SqStack S;
    InitStack(S);

    int num0=1,num1=2*x;

    for(int i=n;i>=2;i--)//i为对应的下标id
        Push(S,i);
    
    while(StackEmpty(S)==false)
    {
        int id;
        Pop(S, id);
        int val=2*x*num1-2*(id-1)*num0;
        
        num0=num1;
        num1=val;
    }
    return num1;
}
```

