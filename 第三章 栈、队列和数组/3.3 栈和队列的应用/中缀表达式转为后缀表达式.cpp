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

bool judge_num(char c)
{
    if(c>='0'&&c<='9')
        return true;
    else return false;
}

int get_priority(char op)
{
    if(op=='+'||op=='-')
        return 1;
    else if(op=='*'||op=='/')
        return 2;
    else 
        return 0;
}

string calc_suffix_expression(string str,int len)
{
    SqStack S;
    InitStack(S);
    string res="";

    for(int i=0;i<len;i++)
    {
        if(judge_num(str[i])==true)
        {
            int j=i;
            while(judge_num(str[j])==true)
            {
                res+=str[j];
                j++;
            }
            i=j-1;
            res+=" ";
        }
        else if(str[i]=='(')
            Push(S, '(');
        else if(str[i]==')')
        {
            while(StackEmpty(S)==false)
            {
                char op;
                Pop(S,op);
                if(op=='(')
                    break;
                res+=op;
                res+=" ";
            }
        }
        else if(str[i]!=' ')
        {
            char op;

            while(StackEmpty(S)==false)
            {
                GetTop(S, op);
                
                if(get_priority(op)<get_priority(str[i]))
                    break;
                Pop(S, op);
                res+=op;
                res+=" ";
            }
            Push(S,str[i]);
        }
    }

    while(StackEmpty(S)==false)
    {
        char op;
        Pop(S,op);
        res+=op;
        res+=" ";
    }

    return res;
}


void Test()
{
    string s1;
    getline(cin,s1);
    
    /*
    12*4+34/5-(56+67*4)+32
    24+2*(5-3)-6/2
    
    */
    
    cout << calc_suffix_expression(s1,s1.size()) << endl;
}


int main()
{
    Test();
    return 0;
}