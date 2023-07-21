#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *prior;
    struct LNode *next;
}LNode,*LinkList;

bool InitList(LinkList &L)//初始化一个循环双链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->prior=L;
    L->next=L;
    return true;
}

bool Empty(LinkList L)//判断双链表是否为空
{
    if(L->next==L)
        return true;
    else return false;
}

bool isTail(LinkList L, LNode *p)//判断是否为表尾节点
{
    if (p->next==L) 
        return true;
    return false;
}

LNode * GetElem(LinkList L,int i)//按位查找操作：返回第i个元素
{
    if(i<0)
        return NULL;
    if(i==0)
        return L;
    LNode *p=L->next;//L指向第一个结点
    int j=1;
    while(p!=L&&j<i)//循环找到第i个结点
    {
        p=p->next;
        j++;
    }
    if(p==L)//都未找到
        return NULL;
    return p;
}

LNode * LocateElem(LinkList L,ElemType e)//按值查找操作：找到数据域==e的结点
{
    LNode *p=L->next;//从第1个结点开始查找数据域为e的结点
    while(p!=L&&p->data!=e)
        p=p->next;
    if(p==L)//都未找到
        return NULL;
    return p;//找到后返回该结点指针,否则返回NULL
}

bool InsertNextNode(LNode *p,ElemType e)//指定结点的后插操作:在p结点之后插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    if(s==NULL)
        return false;
    
    s->data=e;
    s->prior=p;
    p->next->prior=s;
    s->next=p->next;
    p->next=s;//将结点s连到p之后
    return true;
}

bool InsertNextLNode(LNode *p,LNode *s)//指定结点的后插操作:在p结点之后插入结点s
{
    if(p==NULL||s==NULL)
        return false;
    
    s->next=p->next;
    p->next->prior=s;
    s->prior=p;
    p->next=s;
    return true;
}


bool InsertPriorNode(LNode *p,ElemType e)//指定结点的前插操作:在p结点之前插入结点s
{
    return InsertNextNode(p->prior, e);
}

bool InsertPriorLNode(LNode *p,LNode *s)//指定结点的前插操作:在p结点之前插入结点s
{
    return InsertNextLNode(p->prior, s);
}

bool ListInsert(LinkList &L,int i,ElemType e)//按位序插入操作：在表L中的第i个位置上插入指定元素e
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i-1);
    return InsertNextNode(p, e);
}

bool DeleteNode(LNode *s)//指定结点的删除操作：删除指定结点s
{
    if(s==NULL)
        return false;
    
    LNode *p=s->prior;
    p->next=s->next;
    s->next->prior=p;
    free(s);
    return true;
}

bool ListDelete(LinkList &L,int i,ElemType &e)//按位序删除操作(封装)：删除表L中第i个位置的元素，并用e返回删除元素的值
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i);
    if(p==NULL)//i值不合理
        return false;
    return DeleteNode(p);
}


LinkList List_TailInsert(LinkList &L)//尾插法建立循环双链表
{
    ElemType e;
    if(InitList(L)==false)//初始化空链表
        return NULL;
    
    LNode *r=L;//r为表尾指针

    cin >> e;

    while(e!=-1)
    {
        InsertNextNode(r, e);
        r=r->next;
        cin >> e;
    }
    return L;
}

LinkList List_HeadInsert(LinkList &L)//头插法建立循环双链表
{
    ElemType e;
    if(InitList(L)==false)//初始化空链表
        return NULL;

    cin >> e;

    while(e!=-1)
    {
        if(InsertNextNode(L, e)==false)
            return NULL;
        cin >> e;
    }
    return L;
}

int Length(LinkList L)//求表的长度
{
    int len=0;
    LNode *p=L->next;
    while(p!=L)
    {
        p=p->next;
        len++;
    }
    return len;
}

void PrintList(LinkList L)//打印循环双链表
{
    LNode *p=L->next;
    while(p!=L)
    {
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}

void Destroy(LinkList L,LNode *p)//递归释放(辅助函数)
{
    if(p->next!=L)
    {
        Destroy(L, p->next);
        free(p);
    }
}

void DestroyList(LinkList &L)//释放循环双链表
{
    LNode *p=L->next;
    if(p==L)
        free(p);
    else
        Destroy(L, p);
}

bool Judge_Symmetry(LinkList L)
{
    LNode *p=L->next;
    LNode *q=L->prior;

    //偶数的时候q在前面,p在后面,此时q->next==p
    //奇数的时候,两者相遇,p==q
    while(p!=q&&q->next!=p)
    {
        if(p->data==q->data)//相等
        {
            p=p->next;
            q=q->prior;
        }
        else return false;//不相等
    }
    return true;
}


void Test()
{
    LinkList L;
    List_TailInsert(L);   
    /*
        10 16 27 16 10 -1
        10 16 16 10 -1
        2 4 8 7 9 2 7 2 -1
    */            
    PrintList(L);
    
    if(Judge_Symmetry(L)==true)
        cout << "YES" << endl;
    else cout << "NO" << endl;
    
    DestroyList(L);
}

int main()
{
    Test();
    return 0;
}