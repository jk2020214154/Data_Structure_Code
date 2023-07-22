#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *link;
}LNode,*LinkList;


bool InitList(LinkList &L)//初始化一个单链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->link=NULL;
    return true;
}

bool Empty(LinkList L)//判断单链表是否为空
{
    if(L->link==NULL)
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
    s->link=p->link;
    p->link=s;//将结点s连到p之后
    return true;
}

bool InsertPriorNode(LNode *p,ElemType e)//指定结点的前插操作：在p结点之前插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    
    s->link=p->link;
    p->link=s;//新结点s接到p之后
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
        p=p->link;
        j++;
    }
    return p;
}

LNode * LocateElem(LinkList L,ElemType e)//按值查找操作：找到数据域==e的结点
{
    LNode *p=L->link;//从第1个结点开始查找数据域为e的结点
    while(p!=NULL&&p->data!=e)
        p=p->link;
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
        p=p->link;
        j++;
    }

    if(p==NULL)//i值不合法
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    if(s==NULL)
        return false;
    
    s->data=e;//用结点s保存数据元素e
    s->link=p->link;
    p->link=s;//将结点s连到p之后
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
        p=p->link;
        j++;
    }

    if(p==NULL)//i值不合理
        return false;    
    
    if(p->link==NULL)//第i-1个结点之后已无其他结点
        return false;
    
    LNode *s=p->link;//令s指向被删除元素
    e=s->data;//用e返回元素的值
    p->link=s->link;//将*s结点从链中断开
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
    
    if(p->link==NULL)//第i-1个结点之后已无其他结点
        return false;
    
    LNode *s=p->link;//令s指向被删除元素
    e=s->data;//用e返回元素的值
    p->link=s->link;//将*s结点从链中断开
    free(s);//释放结点
    return true;
}


bool DeleteNode(LNode *p)//指定结点的删除操作：删除指定结点p
{
    if(p==NULL)
        return false;
    LNode *s=p->link;//令s指向*p的后继结点
    p->data=p->link->data;
    //和后继结点交换数据域, 若p结点刚好是表L的最后一个结点, 此处会出错, 只能考虑从表头开始依次寻找p的前驱结点
    p->link=s->link;//将*s结点从链中断开
    free(s);
    return true;
}

int Length(LinkList L)//求表的长度
{
    int len=0;
    LNode *p=L->link;
    while(p!=NULL)
    {
        p=p->link;
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
        r->link=s;
        r=s;//r指向新的表尾结点
        cin >> e;
    }
    r->link=NULL;//尾结点指针置空
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
        s->link=L->link;
        L->link=s;//将新结点插入表中, L为头指针
        cin >> e;
    }
    return L;
}

void PrintList(LinkList L)//打印单链表
{
    LNode *p=L->link;
    while(p!=NULL)
    {
        cout << p->data << " ";
        p=p->link;
    }
    cout << endl;
}

void DestroyList(LinkList &L)//释放单链表
{
    if(L!=NULL)
    {
        DestroyList(L->link);
        free(L);
    }
}


void Delete_Abs_Same(LinkList &head,int n)//n为data域的最大范围
{
    int *cnt=(int *)malloc((n+1)*sizeof(int));//记录个数

    for(int i=0;i<=n;i++)//初始化计数数组
        cnt[i]=0;

    LNode *p=head->link,*pre=head;

    while(p!=NULL)
    {
        int num=abs(p->data);
        cnt[num]++;
        if(cnt[num]==1)//第一次出现,后移
        {
            pre=p;
            p=p->link;
        }
        else//重复出现,删除
        {
            LNode *q=p;
            pre->link=p->link;
            p=p->link;
            free(q);
        }
    }

    free(cnt);
}


void Test()
{
    LinkList L;
    List_TailInsert(L);   
    /*
        10 3 3 -16 3 0 16 -3 41 0 -1
        21 -15 -15 -7 15 -1
    */            
    PrintList(L);

    Delete_Abs_Same(L, 100);
    

    PrintList(L);
    
    
    
    DestroyList(L);
}


int main()
{
    Test();
    return 0;
}