#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    int freq;
    struct LNode *prior;
    struct LNode *next;
}LNode,*LinkList;

bool InitList(LinkList &L)//初始化一个双链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->prior=NULL;
    L->next=NULL;
    return true;
}

bool Empty(LinkList L)//判断双链表是否为空
{
    if(L->next==NULL)
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
    else if(i==0)
        return L;
    LNode *p=L;//L指向头结点,头结点是第0个结点
    int j=0;
    while(p!=NULL&&j<i)//循环找到第i个结点
    {
        p=p->next;
        j++;
    }
    return p;
}

LNode * LocateElem(LinkList L,ElemType e)//按值查找操作：找到数据域==e的结点
{
    LNode *p=L->next;//从第1个结点开始查找数据域为e的结点
    while(p!=NULL&&p->data!=e)
        p=p->next;
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
    s->freq=0;
    s->next=NULL;
    s->prior=p;
    
    if(p->next!=NULL)//不为最后一个结点,处理前驱
    {
        p->next->prior=s;
        s->next=p->next;
    }

    p->next=s;//将结点s连到p之后
    return true;
}

bool InsertNextLNode(LNode *p,LNode *s)//指定结点的后插操作:在p结点之后插入结点s
{
    if(p==NULL||s==NULL)
        return false;
    
    s->next=p->next;
    if(p->next!=NULL)
        p->next->prior=s;

    s->prior=p;
    p->next=s;
    return true;
}

bool InsertPriorNode(LNode *p,ElemType e)//指定结点的前插操作:在p结点之前插入结点s
{
    if(p->prior!=NULL)
        return InsertNextNode(p->prior, e);
    return false;
}

bool InsertPriorLNode(LNode *p,LNode *s)//指定结点的前插操作:在p结点之前插入结点s
{
    if(p->prior!=NULL)
        return InsertNextLNode(p->prior, s);
    return false;
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
    if(s->next!=NULL)
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

int Length(LinkList L)//求表的长度
{
    int len=0;
    LNode *p=L->next;
    while(p!=NULL)
    {
        p=p->next;
        len++;
    }
    return len;
}


LinkList List_TailInsert(LinkList &L)//尾插法建立双链表
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
    r->next=NULL;//尾结点指针置空
    return L;
}


LinkList List_HeadInsert(LinkList &L)//头插法建立双链表
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


void PrintList(LinkList L)//打印双链表
{
    LNode *p=L->next;
    while(p!=NULL)
    {
        cout << p->data << " " << p->freq << endl;
        p=p->next;
    }
    cout << endl;
}

void DestroyList(LinkList &L)//释放双链表
{
    if(L!=NULL)
    {
        DestroyList(L->next);
        free(L);
    }
}

LinkList Locate(LinkList &L,ElemType e)//此处前驱用prior,此处的pre与题目的不一样
{
    LNode *p=L->next,*pre;//当前结点,前驱
    while(p!=NULL&&p->data!=e)
        p=p->next;
    
    if(p==NULL)//未找到该值
        exit(0);
    else
    {
        p->freq++;//频率域增加
        if(p->prior==L||p->prior->freq>p->freq)//p是第一个结点或者前驱的值大于当前结点
            return p;
        
        //先将p移除链表
        if(p->next!=NULL)
            p->next->prior=p->prior;
        p->prior->next=p->next;

        //从当前的前驱往前找合适的位置
        pre=p->prior;

        while(pre!=L&&pre->freq<=p->freq)
            pre=pre->prior;

        //将p插入链表中

        p->next=pre->next;
        if(pre->next!=NULL)
            pre->next->prior=p;
        
        p->prior=pre;
        pre->next=p;

    }
    return p;
}

void Test()
{
    LinkList L;
    List_TailInsert(L);   
    /*
        10 16 27 41 -1
    */            
    PrintList(L);

    cout << Locate(L, 21)->data << endl;

    
    
    DestroyList(L);
}

int main()
{
    Test();
    return 0;
}