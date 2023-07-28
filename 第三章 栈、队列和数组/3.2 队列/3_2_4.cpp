#include<iostream>

using namespace std;

typedef int ElemType;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;

typedef struct{//带头结点的循环链队列
    LinkNode *front,*rear;
}LinkQueue;

bool InitQueue(LinkQueue &Q)//初始化
{
    LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
    if(p==NULL)
        return false;
    p->next=Q.front=Q.rear=p;//头结点,front,rear指向头结点
    return true;
}

bool QueueEmpty(LinkQueue Q)//判断队空
{
    if(Q.front==Q.rear)
        return true;
    else return false;
}

bool QueueFull(LinkQueue Q)//判断队满
{
    if(Q.rear->next==Q.front)
        return true;
    else return false;
}

//由于链表方式不存在队满的情况

bool EnQueue(LinkQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)//队满
    {
        LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));

        if(p==NULL)
            return false;
        
        p->data=x;
        p->next=NULL;

        p->next=Q.rear->next;//构成循环队列
        Q.rear->next=p;
        Q.rear=p;
    }
    else//队未满时利用空闲结点
    {
        Q.rear=Q.rear->next;
        Q.rear->data=x;
    }
    return true;
}

bool DeQueue(LinkQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)//空队列
        return false;
    
    
    Q.front=Q.front->next;//后移
    x=Q.front->data;//由于带头结点(此处获取时要先后移)
    return true;
}


bool GetHead(LinkQueue Q,ElemType &x)
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.front->next->data;
    return true;
}


void PrintQueue(LinkQueue &Q)
{
    LinkNode *p=Q.front;
    LinkNode *q=p->next;

    if(QueueFull(Q)==true)
    {
        while(q!=p)
        {
            cout << q->data << " ";
            q=q->next;
        }
    }
    else
    {
        while(q!=Q.rear)
        {
            cout << q->data << " ";
            q=q->next;
        }
    }

    cout << endl;
}





void Test()
{
    LinkQueue Q;
    InitQueue(Q);

    PrintQueue(Q);

    printf("\n队列是否为空：\n");
    int empty;
    empty = QueueEmpty(Q);
    printf("%d\n", empty);
   

    printf("\n将元素入队：\n");
    EnQueue(Q, 11);
    PrintQueue(Q);
    EnQueue(Q, 22);
    PrintQueue(Q);
    EnQueue(Q, 33);
    PrintQueue(Q);
    EnQueue(Q, 44);
    PrintQueue(Q);
    
    printf("\n队列是否已满：\n");
    int full;
    full = QueueFull(Q);
    printf("%d\n", full);

    printf("\n将元素出队：\n");
    int ele;
    DeQueue(Q, ele);
    printf("出队元素：%d\n", ele);
    PrintQueue(Q);
    DeQueue(Q, ele);
    printf("出队元素：%d\n", ele);
    PrintQueue(Q);


    printf("\n队列是否已满：\n");
    full = QueueFull(Q);
    printf("%d\n", full);


    printf("\n将元素入队：\n");
    EnQueue(Q, 55);
    PrintQueue(Q);
    EnQueue(Q, 66);
    PrintQueue(Q);

    printf("\n队列是否已满：\n");
    full = QueueFull(Q);
    printf("%d\n", full);

    printf("\n队头元素：\n");
    int front=-1;
    GetHead(Q, front);
    printf("%d\n", front);


}

int main()
{
    Test();
    return 0;
}