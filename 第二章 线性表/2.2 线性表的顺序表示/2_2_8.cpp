#include<iostream>

using namespace std;

int a[]={0,25,12,3,9};
int b[]={0,42,18,24,52,37,48,7};

#define InitSize 100

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

// bool ChangeList(SeqList &L,int m,int n)
// {
//     if(L.length==0||m<=0||n<=0)
//         return false;
    
//     ElemType *ans=(ElemType *)malloc((m+n)*sizeof(ElemType));

//     for(int i=0;i<m;i++)
//         ans[i+n]=L.data[i];
    
//     for(int i=0;i<n;i++)
//         ans[i]=L.data[i+m];
    
//     for(int i=0;i<m+n;i++)
//         L.data[i]=ans[i];
    
//     free(ans);
//     return true;
// }


void ReverseList(SeqList &L,int start,int length)
{
    for(int i=0;i<length/2;i++)
        swap(L.data[start+i],L.data[start+length-1-i]);
}

bool ChangeList(SeqList &L,int m,int n)
{
    if(L.length==0||m<=0||n<=0)
        return false;
    
    ReverseList(L, 0, m);
    ReverseList(L, m, n);
    ReverseList(L, 0, m+n);
    return true;
}


void Test()
{
    int m=4,n=7;

    SeqList L;
    InitList(L);

    int cnt=0;
    for(int i=1;i<=m;i++)
        ListInsert(L, ++cnt, a[i]);
    for(int i=1;i<=n;i++)
        ListInsert(L, ++cnt, b[i]);
    

    PrintList(L);

    ChangeList(L, m, n);

    PrintList(L);

    DestroyList(L);
}

int main()
{
    Test();
    return 0;
}