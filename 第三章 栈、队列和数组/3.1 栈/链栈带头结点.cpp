#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

//链栈(带头结点)
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
}LNode,*LiStack;

bool InitStack(LiStack &S)//初始化栈
{
    S=(LNode *)malloc(sizeof(LNode));
    if(S==NULL)
        return false;
    S->next=NULL;
    return true;
}

bool StackEmpty(LiStack S)//判断栈空
{
    if(S->next==NULL)
        return true;
    else return false;
}


bool Push(LiStack &S,ElemType x)//入栈
{
    LNode *p=(LNode *)malloc(sizeof(LNode));

    if(p==NULL)
        return false;
    //头插法
    p->data=x;
    p->next=S->next;
    S->next=p;
    return true;
}

bool Pop(LiStack &S,ElemType &x)//出栈
{
    if(S->next==NULL)
        return false;
    
    LNode *p=S->next;
    x=p->data;
    S->next=p->next;
    free(p);
    return true;
}

bool GetTop(LiStack S,ElemType &x)//取栈顶元素
{
    if(S->next==NULL)
        return false;
    
    x=S->next->data;
    return true;
}


void DestroyStack(LiStack &S)
{
    ElemType x;
    while(S->next!=NULL)
        Pop(S,x);
    free(S);
} 

void PrintStack(LiStack S)
{
    if(StackEmpty(S)==true)
    {
        cout << "当前栈空" << endl;
        return ;
    }
    LNode *p=S->next;
    while(p!=NULL)
    {
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}


void Test()
{
    LiStack S;
    InitStack(S);

    ElemType num=-1;

    Push(S,3);
    Push(S,6);
    Push(S,1);



    GetTop(S, num);

    cout << num << endl;

    Push(S,2);
    Push(S,7);

    PrintStack(S);
    
    num=-1;
    GetTop(S, num);

    cout << num << endl;    
    
    num=-1;
    Pop(S,num);

    PrintStack(S);
    
    Push(S, 54);
    
    PrintStack(S);
    
    num=-1;
    Pop(S,num);
    
    cout << num << endl;
    
    PrintStack(S);

    DestroyStack(S);
    
}


int main()
{
    Test();
    return 0;
}