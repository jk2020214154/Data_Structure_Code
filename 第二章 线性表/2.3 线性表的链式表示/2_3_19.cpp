#include<iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;


bool InitList(LinkList &L)//初始化一个循环单链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next=L;//自己的后继指向自己
    return true;
}

bool Empty(LinkList L)//判断循环单链表是否为空
{
    if(L->next==L)
        return true;
    else return false;
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

LNode * GetElem(LinkList L,int i)//按位查找操作：返回第i个元素
{
    if(i<0)
        return NULL;
    else if(i==0)
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
    
    s->data=e;//用结点s保存数据元素e
    s->next=p->next;
    p->next=s;//将结点s连到p之后
    return true;
}

bool ListInsert(LinkList &L,int i,ElemType e)//按位序插入操作(封装)：在表L中的第i个位置上插入指定元素e
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i-1);
    return InsertNextNode(p, e);
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

bool InsertPriorLNode(LNode *p,LNode *s)//指定结点的前插操作：在p结点之前插入结点s
{
    if(p==NULL||s==NULL)
        return false;
    
    s->next=p->next;
    p->next=s;
    swap(s->data,p->data);//后插,然后交换元素
    return true;
}

bool ListDelete(LinkList &L,int i,ElemType &e)//按位序删除操作(封装)：删除表L中第i个位置的元素，并用e返回删除元素的值
{
    if(i<1)
        return false;
    LNode *p=GetElem(L, i-1);
    if(p==NULL)//i值不合理
        return false;    
    
    if(p->next==L)//第i-1个结点之后已无其他结点(指向头结点)
        return false;
    
    LNode *s=p->next;//令s指向被删除元素
    e=s->data;//用e返回元素的值
    p->next=s->next;//将*s结点从链中断开
    free(s);//释放结点
    return true;
}

bool DeleteNode(LinkList &L,LNode *p)//指定结点的删除操作：删除指定结点p
{
    if(p==NULL)
        return false;
    LNode *s=p->next;//令s指向*p的后继结点
    p->data=p->next->data;
    //和后继结点交换数据域, 若p结点刚好是表L的最后一个结点, 此处会出错, 只能考虑从表头开始依次寻找p的前驱结点
    p->next=s->next;//将*s结点从链中断开

    if(L==s)//如果p的后继结点是头结点
        L=p;//让头结点指向原来头结点的后继结点(删除头结点)
    free(s);
    return true;
}

LinkList List_TailInsert(LinkList &L)//尾插法建立循环单链表
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
    r->next=L;//尾结点指针置为L
    return L;
}

LinkList List_HeadInsert(LinkList &L)//头插法建立循环单链表
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

void PrintList(LinkList L)//打印循环单链表
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

void DestroyList(LinkList &L)//释放循环单链表
{
    LNode *p=L->next;
    if(p==L)
        free(p);
    else
        Destroy(L, p);
}


void Sort_And_Delete(LinkList &L)
{
    while(L->next!=L)
    {
        LNode *p=L->next,*pre=L;
        LNode *p_min=L->next;//记录最小值的指针
        LNode *pre_min=L;//记录最小值的前驱指针(方便后续更改)
        ElemType num;

        while(p!=L)
        {
            if(p->data<p_min->data)
            {
                p_min=p;
                pre_min=pre;
            }
            pre=p;
            p=p->next;
        }

        pre_min->next=p_min->next;
        num=p_min->data;
        cout << num << " ";
        free(p_min);
    }
    cout << endl;
}



LinkList Delete_Min_Elem(LinkList L,ElemType &e)//辅助函数
{
    LNode *p=L->next,*pre=L;
    LNode *p_min=L->next;//记录最小值的指针
    LNode *pre_min=L;//记录最小值的前驱指针(方便后续更改)

    while(p!=L)
    {
        if(p->data<p_min->data)
        {
            p_min=p;
            pre_min=pre;
        }
        pre=p;
        p=p->next;
    }

    pre_min->next=p_min->next;
    e=p_min->data;
    free(p_min);

    return L;
}

void Sort_And_Delete_short(LinkList &L)
{
    while(L->next!=L)
    {
        ElemType num;
        Delete_Min_Elem(L, num);
        cout << num << " ";
    }
    cout << endl;
    free(L);
}



void Test()
{
    LinkList L;
    List_TailInsert(L);   
    /*
        10 3 3 16 3 27 3 41 -1
        
        3 1 2 4 5 -1
    */            
    PrintList(L);
    
    //Sort_And_Delete(L);
    //Sort_And_Delete_short(L);

    //PrintList(L);           
    
    //DestroyList(L);
}


int main()
{
    Test();
    return 0;
}