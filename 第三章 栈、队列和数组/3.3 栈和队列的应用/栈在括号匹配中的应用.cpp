#include<iostream>

using namespace std;

#define MaxSize 110

typedef char ElemType;

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

            if(str[i]==')'&&x!='(')
                return false;
            if(str[i]==']'&&x!='[')
                return false;
            if(str[i]=='}'&&x!='{')
                return false;
        }
    }
    return StackEmpty(S);
}


void Test()
{
    string s;
    cin >> s;
    /*
        {(())[]}
        {(()][]}
        {(())}]()
        {{(())[]}
    */

    if(bracketCheck(s,s.size())==true)
        cout << "匹配成功" << endl;
    else cout << "匹配失败" << endl;
}


int main()
{
    Test();
    return 0;
}