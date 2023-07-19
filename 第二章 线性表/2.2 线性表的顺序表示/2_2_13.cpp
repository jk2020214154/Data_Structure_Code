#include<iostream>
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

int a[]={0,-5,3,2,3};
int b[]={0,1,2,3};

int Search_Min_Positive_Integer(SeqList L,int n)
{
    int *flag=(int *)malloc((n+1)*sizeof(int));

    for(int i=1;i<=n;i++)
        flag[i]=0;

    for(int i=0;i<n;i++)
        if(L.data[i]>=1&&L.data[i]<=n)
            flag[L.data[i]]=1;
    int ans=n+1;
    for(int i=1;i<=n;i++)
        if(flag[i]==0)
        {
            ans=i;
            break;
        }
    
    free(flag);
    return ans;
}




void Test()
{
    int n=4,m=3;
    SeqList L1,L2;
    InitList(L1);
    InitList(L2);

    for(int i=1;i<=n;i++)
        ListInsert(L1, i, a[i]);

    for(int i=1;i<=m;i++)
        ListInsert(L2, i, b[i]);
    
    PrintList(L1);
    PrintList(L2);

    cout << Search_Min_Positive_Integer(L1, n) << endl;
    cout << Search_Min_Positive_Integer(L2, m) << endl;
\left| \right|    
   
    
    DestroyList(L1);
    DestroyList(L2);
}


int main()
{
    Test();
    return 0;
}