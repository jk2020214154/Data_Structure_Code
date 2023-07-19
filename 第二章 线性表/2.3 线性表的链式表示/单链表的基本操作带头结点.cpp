#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;


bool InitList(LinkList &L)//初始化一个单链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next=NULL;
    return true;
}

bool Empty(LinkList L)//判断单链表是否为空
{
    if(L->next==NULL)
        return true;
    else return false;
}

bool InsertNextNode(LNode *p,ElemType e)//指定结点的后插操作:在p结点之后插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    if(s==NULL)
        return false;
    
    s->data=e;//用结点s保存数据元素e
    s->next=p->next;
    p->next=s;//将结点s连到p之后
    return true;
}

bool InsertPriorNode(LNode *p,ElemType e)//指定结点的前插操作：在p结点之前插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    
    s->next=p->next;
    p->next=s;//新结点s接到p之后
    s->data=p->data;//将p中的元素复制到s中
    p->data=e;//p中元素覆盖为e
    return true;
}


LNode * GetElem(LinkList L,int i)//按位查找操作：返回第i个元素
{
    if(i<0)
        return NULL;
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

bool ListInsert(LinkList &L,int i,ElemType e)//按位序插入操作：在表L中的第i个位置上插入指定元素e
{
    if(i<1)
        return false;
    LNode *p=L;//L指向头结点,头结点是第0个结点
    int j=0;
    while(p!=NULL&&j<i-1)//循环找到第i-1个结点
    {
        p=p->next;
        j++;
    }

    if(p==NULL)//i值不合法
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    if(s==NULL)
        return false;
    
    s->data=e;//用结点s保存数据元素e
    s->next=p->next;
    p->next=s;//将结点s连到p之后
    return true;
}

bool ListInsert_short(LinkList &L,int i,ElemType e)//按位序插入操作(封装)：在表L中的第i个位置上插入指定元素e
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i-1);
    return InsertNextNode(p, e);
}

bool ListDelete(LinkList &L,int i,ElemType &e)//按位序删除操作：删除表L中第i个位置的元素，并用e返回删除元素的值
{
    if(i<1)
        return false;
    LNode *p=L;//L指向头结点,头结点是第0个结点
    int j=0;
    while(p!=NULL&&j<i-1)//循环找到第i-1个结点
    {
        p=p->next;
        j++;
    }

    if(p==NULL)//i值不合理
        return false;    
    
    if(p->next==NULL)//第i-1个结点之后已无其他结点
        return false;
    
    LNode *s=p->next;//令s指向被删除元素
    e=s->data;//用e返回元素的值
    p->next=s->next;//将*s结点从链中断开
    free(s);//释放结点
    return true;
}

bool ListDelete_short(LinkList &L,int i,ElemType &e)//按位序删除操作(封装)：删除表L中第i个位置的元素，并用e返回删除元素的值
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i-1);
    if(p==NULL)//i值不合理
        return false;    
    
    if(p->next==NULL)//第i-1个结点之后已无其他结点
        return false;
    
    LNode *s=p->next;//令s指向被删除元素
    e=s->data;//用e返回元素的值
    p->next=s->next;//将*s结点从链中断开
    free(s);//释放结点
    return true;
}


bool DeleteNode(LNode *p)//指定结点的删除操作：删除指定结点p
{
    if(p==NULL)
        return false;
    LNode *s=p->next;//令s指向*p的后继结点
    p->data=p->next->data;
    //和后继结点交换数据域, 若p结点刚好是表L的最后一个结点, 此处会出错, 只能考虑从表头开始依次寻找p的前驱结点
    p->next=s->next;//将*s结点从链中断开
    free(s);
    return true;
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

LinkList List_TailInsert(LinkList &L)//尾插法建立单链表
{
    ElemType e;
    if(InitList(L)==false)//初始化空链表
        return NULL;
    
    LNode *s,*r=L;//r为表尾指针

    cin >> e;

    while(e!=-1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s==NULL)
            return NULL;
        s->data=e;
        r->next=s;
        r=s;//r指向新的表尾结点
        cin >> e;
    }
    r->next=NULL;//尾结点指针置空
    return L;
}


LinkList List_HeadInsert(LinkList &L)//头插法建立单链表
{
    ElemType e;
    if(InitList(L)==false)//初始化空链表
        return NULL;
    
    LNode *s;

    cin >> e;

    while(e!=-1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s==NULL)
            return NULL;
        s->data=e;
        s->next=L->next;
        L->next=s;//将新结点插入表中, L为头指针
        cin >> e;
    }
    return L;
}

void PrintList(LinkList L)//打印单链表
{
    LNode *p=L->next;
    while(p!=NULL)
    {
        cout << p->data << " ";
        p=p->next;
    }
    cout << endl;
}

void DestroyList(LinkList &L)//释放单链表
{
    if(L!=NULL)
    {
        DestroyList(L->next);
        free(L);
    }
}



void Test()
{
    LinkList L;
    List_TailInsert(L);   
    /*
        10 16 27 41 -1
    */            
    PrintList(L);
    InsertNextNode(GetElem(L, 3), 666);
    PrintList(L);           
    InsertPriorNode(LocateElem(L, 666), 777);
    PrintList(L);
    ListInsert(L, 3, 888);
    PrintList(L);
    ElemType e = -1;
    ListDelete(L, 5, e);
    DeleteNode(GetElem(L, 2));
    printf("表长=%d\n", Length(L));
    
    
    DestroyList(L);
}


int main()
{
    Test();
    return 0;
}