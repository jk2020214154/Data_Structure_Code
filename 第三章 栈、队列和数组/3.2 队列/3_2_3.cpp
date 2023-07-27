#include<iostream>

using namespace std;

#define MaxSize 5

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

bool StackOverflow(SqStack S)
{
    if(S.top==MaxSize-1)
        return true;
    else return false;
}

bool EnQueue(SqStack &S1,SqStack &S2,ElemType x)//入队
{
    if(StackOverflow(S1)==false)//S1未满,放入S1中
    {
        Push(S1,x);
        return true;
    }
    if(StackOverflow(S1)==true&&StackEmpty(S2)==false)
    {
        //S1满了,且S2有元素
        cout << "队列满" << endl;
        return 0;
    }
    if(StackOverflow(S1)==true&&StackEmpty(S2)==true)
    {
        //S1满了,S2空
        ElemType num;
        while(StackEmpty(S1)==false)
        {
            Pop(S1,num);
            Push(S2,num);
        }
    }

    Push(S1,x);
    return true;
}

bool DeQueue(SqStack &S1,SqStack &S2,ElemType &x)//出队列
{
    if(StackEmpty(S2)==false)//S2不空
    {
        Pop(S2,x);
        return true;
    }
    else if(StackEmpty(S1)==true)//S2为空,S1为空
    {
        cout << "队列空" << endl;
        return 0;
    }
    else//S2为空,S1不为空
    {
        ElemType num;
        while(StackEmpty(S1)==false)
        {
            Pop(S1, num);
            Push(S2,num);
        }
        Pop(S2,x);
        return true;
    }
}

bool QueueEmpty(SqStack S1,SqStack S2)//判断队空
{
    if(StackEmpty(S1)==true&&StackEmpty(S2)==true)
        return true;
    else return false;
}

void Print_Two_Stack(SqStack S1,SqStack S2)
{
    for(int i=0;i<=S1.top;i++)
        cout << S1.data[i] << " ";
    cout << endl;

    for(int i=0;i<=S2.top;i++)
        cout << S2.data[i] << " ";
    cout << endl << "------------" << endl;
}

void Test()
{
    SqStack S1,S2;
    ElemType num;
    //S1为输入栈,S2为输出栈
    InitStack(S1);
    InitStack(S2);
    
    //DeQueue(S1,S2,num);

    for(int i=1;i<=4;i++)
        EnQueue(S1, S2, i);
    
    Print_Two_Stack(S1, S2);

    DeQueue(S1, S2, num);
    Print_Two_Stack(S1, S2);

    for(int i=5;i<=10;i++)
        EnQueue(S1, S2, i);
    
    Print_Two_Stack(S1, S2);

}


int main()
{
    Test();
    return 0;
}