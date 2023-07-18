#include <errno.h>
#include<iostream>
#include <limits.h>
using namespace std;

#define MaxSize 50

typedef int ElemType;

typedef struct{
    ElemType data[MaxSize];
    int length;
}SqList;


void InitList(SqList &L)//初始化
{
    for(int i=0;i<MaxSize;i++)
        L.data[i]=0;
    L.length=0;
}


bool ListInsert(SqList &L,int i,ElemType e)//插入操作
{
    if(i<1||i>L.length+1)
        return false;
    if(L.length>=MaxSize)
        return false;
    
    for(int j=L.length;j>=i;j--)
        L.data[j]=L.data[j-1];
    
    L.data[i-1]=e;
    L.length++;
    return true;
}

bool ListDelete(SqList &L,int i,ElemType &e)//删除操作
{
    if(i<1||i>L.length)
        return false;
    
    e=L.data[i-1];
    for(int j=i;j<L.length;j++)
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}

ElemType GetElem(SqList L,int i)//按位查找
{
    if(i>=1&&i<=L.length)
        return L.data[i-1];
    else return INT_MIN;
}

int LocateElem(SqList L,ElemType e)//按值查找第一个值为e的位置
{
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1;
    return -1;
}

int getLength(SqList L)//获取线性表的长度
{
    return L.length;
}

void PrintList(SqList L)//打印线性表的数据元素
{
    for(int i=0;i<L.length;i++)
        cout << L.data[i] << " ";
    cout << endl;
}

bool Empty(SqList L)//判断线性表是否为空
{
    return L.length==0;
}

void DestroyList(SqList &L)//销毁线性表
{
    ;//由于是数组可不用进行销毁
}


void Test()
{
    SqList L;

    InitList(L);

    cout << Empty(L) << endl;

    ListInsert(L, 1, 86);
    PrintList(L);

    ListInsert(L, 2, 8);
    PrintList(L);

    ListInsert(L, 2, 5);
    PrintList(L);

    ListInsert(L, 1, 14);

    cout << GetElem(L, 100) << endl;
    cout << LocateElem(L, 8) << endl;

    PrintList(L);

    ElemType num;
    ListDelete(L, 3, num);

    cout << num << endl;
    PrintList(L);

    cout << getLength(L) << endl;
}


int main()
{
    Test();
    return 0;
}