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

// int P(int n,int x)
// {
//     if(n==0)
//         return 1;
//     else if(n==1)
//         return 2*x;
//     else return 2*x*P(n-1,x)-2*(n-1)*P(n-2,x);
// }

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

void Test()
{
    int n,x;
    cin >> n >> x;
    
    /*
        3 2     40
    
    */
    cout << P(n,x) << endl;
}

int main()
{
    Test();
    return 0;
}