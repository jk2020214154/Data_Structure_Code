#include<iostream>

using namespace std;

#define MaxSize 50

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


//front指向队头元素,rear指向队尾元素的下一个位置
//front=0,rear=0
//牺牲一个空间
typedef struct {
    ElemType data[MaxSize];
    int front,rear; 
}SqQueue;


void InitQueue(SqQueue &Q)//初始化
{
    Q.front=Q.rear=0;
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if(Q.rear==Q.front)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    if((Q.rear+1)%MaxSize==Q.front)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    return true;
}

bool GetHead(SqQueue Q,ElemType &x)//获取队头
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    return true;
}


void DestroyQueue(SqQueue &Q)//销毁队列
{
    //由于是静态分配,不用释放
    ElemType num;
    while(QueueEmpty(Q)==false)
        DeQueue(Q, num);
}


void PrintQueue(SqQueue Q)//打印队列
{
    //cout << "-------------------------" << endl;
    //cout << Q.front << " " << Q.rear << endl;

    int pos=Q.front;

    while(pos!=Q.rear)
    {
        cout << Q.data[pos] << " ";
        pos=(pos+1)%MaxSize;
    }
    cout << endl;
}


void Reverse_Queue(SqQueue &Q,SqStack &S)
{
    ElemType num;
    while(QueueEmpty(Q)==false)
    {
        DeQueue(Q, num);//出队列
        Push(S, num);//入栈
    }

    while(StackEmpty(S)==false)
    {
        Pop(S, num);//出栈
        EnQueue(Q, num);//入队列
    }
}

void Test()
{
   SqStack S;
   SqQueue Q;
   InitStack(S);
   InitQueue(Q);

   for(int i=1;i<=10;i++)
        EnQueue(Q, i);
    
    PrintQueue(Q);
   
    Reverse_Queue(Q,S);

    PrintQueue(Q);

    DestroyQueue(Q);
}


int main()
{
    Test();
    return 0;
}