#include<iostream>

using namespace std;

#define MaxSize 10

typedef int ElemType;


//front指向队头元素,rear指向队尾元素
//front=0,rear=-1/MaxSize-1
//牺牲一个空间
typedef struct {
    ElemType data[MaxSize];
    int front,rear; 
}SqQueue;


void InitQueue(SqQueue &Q)//初始化
{
    Q.front=0;
    Q.rear=MaxSize-1;//此处可置为-1
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if((Q.rear+1)%MaxSize==Q.front)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    if((Q.rear+2)%MaxSize==Q.front)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.rear=(Q.rear+1)%MaxSize;//注意入队先+1,再赋值
    Q.data[Q.rear]=x;
    
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
    ElemType num;
    while(QueueEmpty(Q)==false)
        DeQueue(Q, num);
}


void PrintQueue(SqQueue Q)//打印队列
{
    //cout << "-------------------------" << endl;
    //cout << Q.front << " " << Q.rear << endl;
    
    if(QueueEmpty(Q)==false)
    {
        int pos=Q.front;
    
        while(pos!=Q.rear)
        {
            cout << Q.data[pos] << " ";
            pos=(pos+1)%MaxSize;
        }
        
        cout << Q.data[Q.rear] << " ";
    }
    cout << endl;
}




void Test()
{
    SqQueue Q;
    InitQueue(Q);


    //PrintQueue(Q);
    for(int i=1;i<=15;i++)
    {
        EnQueue(Q, i);
        
        ElemType num;
        if(i>=3&&i<=6)
            DeQueue(Q,num);
        PrintQueue(Q);
    }

    DestroyQueue(Q);
}

int main()
{
    Test();
    return 0;
}