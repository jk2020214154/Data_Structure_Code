#include <errno.h>
#include<iostream>
#include <limits.h>
using namespace std;

#define InitSize 10

typedef int ElemType;

typedef struct{
    ElemType *data;
    int MaxSize;
    int length;
}SeqList;


void InitList(SeqList &L)//初始化
{
    L.data=(ElemType*)malloc(InitSize*sizeof(ElemType));
    if(L.data==NULL)
        exit(1);
    L.length=0;
    L.MaxSize=InitSize;
}

bool IncreaseSize(SeqList &L,int len)//增加动态数组长度(辅助函数)
{
    ElemType *p=L.data;
    L.data=(ElemType*)malloc((L.MaxSize+len)*sizeof(ElemType));

    if(L.data==NULL)
        return false;
    for(int i=0;i<L.length;i++)
        L.data[i]=p[i];
    
    L.MaxSize=L.MaxSize+len;
    free(p);
    return true;
}

bool ListInsert(SeqList &L,int i,ElemType e)//插入操作
{
    if(i<1||i>L.length+1)
        return false;
    if(L.length>=L.MaxSize)
    {
        bool status=IncreaseSize(L, 10);
        if(status==false)
            return false;
    }

    for(int j=L.length;j>=i;j--)
        L.data[j]=L.data[j-1];
    
    L.data[i-1]=e;
    L.length++;
    return true;
}


bool ListDelete(SeqList &L,int i,ElemType &e)//删除操作
{
    if(i<1||i>L.length)
        return false;
    
    e=L.data[i-1];
    for(int j=i;j<L.length;j++)
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}


ElemType GetElem(SeqList L,int i)//按位查找
{
    if(i>=1&&i<=L.length)
        return L.data[i-1];
    else return INT_MIN;
}

int LocateElem(SeqList L,ElemType e)//按值查找第一个值为e的位置
{
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1;
    return -1;
}

int getLength(SeqList L)//获取线性表的长度
{
    return L.length;
}

void PrintList(SeqList L)//打印线性表的数据元素
{
    for(int i=0;i<L.length;i++)
        cout << L.data[i] << " ";
    cout << endl;
}

bool Empty(SeqList L)//判断线性表是否为空
{
    return L.length==0;
}

void DestroyList(SeqList &L)//销毁线性表
{
    free(L.data);
    L.length=0;
}

bool MergeList(SeqList A,SeqList B,SeqList &C)
{
    if(A.length+B.length>C.MaxSize)
        return false;
    
    int i=0,j=0,cnt=0;

    while(i<A.length&&j<B.length)
    {
        if(A.data[i]<=B.data[j])
            C.data[cnt++]=A.data[i++];
        else C.data[cnt++]=B.data[j++];
    }

    while(i<A.length)
        C.data[cnt++]=A.data[i++];
    
    while(j<B.length)
        C.data[cnt++]=B.data[j++];
    
    C.length=A.length+B.length;

    return true;
}


void Test()
{
    SeqList L1,L2,L;

    InitList(L);
    InitList(L1);
    InitList(L2);
    
    ListInsert(L1, 1, 1);
    ListInsert(L1, 2, 3);
    ListInsert(L1, 3, 5);
    
    ListInsert(L2, 1, 2);
    ListInsert(L2, 2, 4);
    ListInsert(L2, 3, 5);

    PrintList(L1);
    PrintList(L2);

    PrintList(L);

    MergeList(L1,L2,L);

    PrintList(L);

    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L);
}


int main()
{
    Test();
    return 0;
}