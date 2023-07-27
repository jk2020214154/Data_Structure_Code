#include<iostream>

using namespace std;

typedef int ElemType;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;

typedef struct{//不带头结点的链队列
    LinkNode *front,*rear;
}LinkQueue;

bool InitQueue(LinkQueue &Q)//初始化
{
    Q.front=Q.rear=NULL;
    return true;
}

bool QueueEmpty(LinkQueue Q)//判断队空
{
    if(Q.front==NULL)
        return true;
    else return false;
}

//由于链表方式不存在队满的情况

bool EnQueue(LinkQueue &Q,ElemType x)//入队
{
    LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));

    if(p==NULL)
        return false;
    
    p->data=x;
    p->next=NULL;

    if(QueueEmpty(Q)==true)
    {
        Q.front=Q.rear=p;
    }
    else
    {
        Q.rear->next=p;
        Q.rear=p;        
    }
    return true;
}

bool DeQueue(LinkQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)//空队列
        return false;
    
    LinkNode *p=Q.front;

    x=p->data;
    Q.front=p->next;

    if(p==Q.rear)//最后一个元素
        Q.rear=Q.front=NULL;//置为空
    free(p);

    return true;
}


bool GetHead(LinkQueue Q,ElemType &x)
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.front->data;
    return true;
}


void PrintQueue(LinkQueue &Q)
{
    if(QueueEmpty(Q)==false)
    {
        LinkNode *p=Q.front;

        while(p!=NULL)
        {
            cout << p->data << " ";
            p=p->next;
        }
    }
    cout << endl;
}




void DestroyQueue(LinkQueue &Q)
{
    while(QueueEmpty(Q)==false)
    {
        ElemType num;
        DeQueue(Q, num);
    }
}



void Test()
{
    LinkQueue Q;
    InitQueue(Q);

    for(int i=1;i<=15;i++)
    {
        EnQueue(Q, i);
        
        ElemType num;
        if(i>=3&&i<=6)
            DeQueue(Q,num);
        
        GetHead(Q,num);
        cout << num << "------------" << endl;
        PrintQueue(Q);
    }

    DestroyQueue(Q);
}

int main()
{
    Test();
    return 0;
}