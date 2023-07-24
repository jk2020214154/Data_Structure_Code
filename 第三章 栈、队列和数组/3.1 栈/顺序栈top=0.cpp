#include<iostream>

using namespace std;

#define MaxSize 50

typedef int ElemType;

//顺序栈(top初始为0--->指向栈顶元素的下一个位置)
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S)//栈的初始化
{
    S.top=0;//初始化需更改
}

//判断条件需更改

bool StackEmpty(SqStack S)//判断栈空
{
    if(S.top==0)//这里
        return true;
    else return false;
}

bool Push(SqStack &S,ElemType x)//进栈
{
    if(S.top==MaxSize)//这里
        return false;
    S.data[S.top++]=x;//注意是后++
    return true;
}

bool Pop(SqStack &S,ElemType &x)//出栈
{
    if(S.top==0)//这里
        return false;
    
    x=S.data[--S.top];//注意是前--
    return true;
}

bool GetTop(SqStack S,ElemType &x)//获取栈顶
{
    if(S.top==0)//这里
        return false;
    x=S.data[S.top-1];//注意获取时需-1
    return true;
}

void DestroyStack(SqStack &S)//销毁栈
{
    //由于是静态分配,不用释放
}


void Test()
{
    SqStack S;
    InitStack(S);

    ElemType num;

    Push(S,3);
    Push(S,6);
    Push(S,1);

    GetTop(S, num);

    cout << num << endl;

    Push(S,2);
    Push(S,7);
    
    GetTop(S, num);

    cout << num << endl;    

    Pop(S,num);

    
    Push(S, 54);
    Pop(S,num);
    
    cout << num << endl;

}


int main()
{
    Test();
    return 0;
}