#include<iostream>

using namespace std;

#define MaxSize 110

typedef int ElemType;

//顺序栈(top初始为-1--->指向栈顶元素的当前位置)
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S)//栈的初始化
{
    S.top=-1;
}

bool StackEmpty(SqStack S)//判断栈空
{
    if(S.top==-1)
        return true;
    else return false;
}

bool Push(SqStack &S,ElemType x)//进栈
{
    if(S.top==MaxSize-1)
        return false;
    S.data[++S.top]=x;
    return true;
}

bool Pop(SqStack &S,ElemType &x)//出栈
{
    if(S.top==-1)
        return false;
    
    x=S.data[S.top--];
    return true;
}

bool GetTop(SqStack S,ElemType &x)//获取栈顶
{
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    return true;
}

void DestroyStack(SqStack &S)//销毁栈
{
    //由于是静态分配,不用释放
}

int op_calc(int a,int b,char op)
{
    if(op=='+')
        return a+b;
    else if(op=='-')
        return a-b;
    else if(op=='*')
        return a*b;
    else return a/b;
}

bool judge_num(char c)
{
    if(c>='0'&&c<='9')
        return true;
    else return false;
}

int calc_value(string str,int len)
{
    SqStack S;
    InitStack(S);

    for(int i=0;i<len;i++)
    {
        if(judge_num(str[i])==true)
        {
            int j=i;
            int num=0;
            while(judge_num(str[j])==true)
            {
                num=num*10+(str[j]-'0');
                j++;
            }

            i=j-1;
            Push(S, num);
        }
        else if(str[i]!=' ')
        {
            int num1=0,num2=0;
            Pop(S, num2);
            Pop(S, num1);

            cout << num1 << " " << num2 << " " << str[i] << endl;
            Push(S,op_calc(num1, num2, str[i]));
        }
    }
    int res=0;
    GetTop(S, res);

    return res;
}



void Test()
{
    string s;
    getline(cin,s);
    //保证输入的后缀表达式合法
    /*
    9 3 1 - 3 * + 10 2 / +
    13 445 + 51 / 6 -
    35 15 + 80 70 - * 20 /
    
    12 4 * 34 5 / + 56 67 4 * + - 32 + 
    24 2 5 3 - * + 6 2 / - 

    */
    //cin >> s;
    //cout << s << endl;
    cout << calc_value(s,s.size()) << endl;
}

int main()
{
    Test();
    return 0;
}