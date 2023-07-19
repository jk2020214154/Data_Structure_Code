#include<iostream>
#include <limits.h>
#include <stdlib.h>
using namespace std;

#define InitSize 5

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

int a[]={0,-1,0,9};
int b[]={0,-25,-10,10,11};
int c[]={0,2,9,17,30,41};

int calc_dist(int x,int y,int z)
{
    return abs(x-y)+abs(y-z)+abs(z-x);
}

// int Calc_Min_Dist(SeqList A,SeqList B,SeqList C)
// {
//     if(A.length==0||B.length==0||C.length==0)
//         return -1;
    
//     int ans=calc_dist(A.data[0], B.data[0], C.data[0]);//初始值置为某一个值

//     for(int i=0;i<A.length;i++)
//         for(int j=0;j<B.length;j++)
//             for(int k=0;k<C.length;k++)
//                 ans=min(ans,calc_dist(A.data[i], B.data[j], C.data[k]));
//     return ans;
// }

bool check_min(int a,int b,int c)
{
    return (a<=b&&a<=c);
}

int Calc_Min_Dist(SeqList A,SeqList B,SeqList C)
{
    if(A.length==0||B.length==0||C.length==0)
        return -1;
    int ans=calc_dist(A.data[0], B.data[0], C.data[0]);//初始值置为某一个值

    int i=0,j=0,k=0;

    while(i<A.length&&j<B.length&&k<C.length)
    {
        ans=min(ans,calc_dist(A.data[i], B.data[j], C.data[k]));

        if(check_min(A.data[i], B.data[j], C.data[k]))
            i++;
        else if(check_min(B.data[j], A.data[i], C.data[k]))
            j++;
        else k++;
    }
    return ans;
}



void Test()
{
    int n=3,m=4,p=5;
    SeqList L1,L2,L3;
    InitList(L1);
    InitList(L2);
    InitList(L3);

    for(int i=1;i<=n;i++)
        ListInsert(L1, i, a[i]);

    for(int i=1;i<=m;i++)
        ListInsert(L2, i, b[i]);
    
    for(int i=1;i<=p;i++)
        ListInsert(L3, i, c[i]);
    
    PrintList(L1);
    PrintList(L2);
    PrintList(L3);

    cout << Calc_Min_Dist(L1, L2, L3) << endl;
   
    
    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L3);
}


int main()
{
    Test();
    return 0;
}