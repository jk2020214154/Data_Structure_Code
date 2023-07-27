#include<iostream>

using namespace std;

#define MaxSize 10

typedef int ElemType;


//front指向队头元素,rear指向队尾元素
//front=0,rear=-1/MaxSize-1
//增加元素个数统计
typedef struct {
    ElemType data[MaxSize];
    int front,rear;
    int size;
}SqQueue;


void InitQueue(SqQueue &Q)//初始化
{
    Q.front=Q.size=0;
    Q.rear=MaxSize-1;
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if(Q.size==0)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    //cout << Q.size << " " << MaxSize << endl;
    if(Q.size==MaxSize)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.rear=(Q.rear+1)%MaxSize;//注意入队先+1,再赋值
    Q.data[Q.rear]=x;
    
    Q.size++;//个数加一
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    Q.size--;//各数减一
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

    //cout << Q.size << endl;
    int pos=Q.front;
    int cnt=0;
    while(cnt<Q.size)
    {
        cout << Q.data[pos] << " ";
        pos=(pos+1)%MaxSize;
        cnt++;
    }
    cout << endl;
}



void Test()
{
    SqQueue Q;
    InitQueue(Q);

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