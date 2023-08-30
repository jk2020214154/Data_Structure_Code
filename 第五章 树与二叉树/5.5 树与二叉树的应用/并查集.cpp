#include<iostream>

using namespace std;


#define SIZE 110

void Initial(int S[])//并查集的初始化
{
    for(int i=0;i<SIZE;i++)
        S[i]=-1;
}

int Find(int S[],int x)//并查集的查询操作(主要)
{
    while(S[x]>=0)//循环找到x的根
        x=S[x];
    return x;//根的S[]小于0
}

// int Find_Optimize(int S[],int x)//并查集的查询优化操作(主要)
// {
    // int root=x;
    // while(S[root]>=0)//循环找到根
        // root=S[root];
    // while(x!=root)
    // {
        // int t=S[x];
        // S[x]=root;
        // x=t;
    // }
    // return root;
// }

int Find_Optimize(int S[],int x)//并查集的查询优化操作(主要)
{
    if(S[x]>=0)
        return S[x]=Find_Optimize(S,S[x]);
    return x;
}



void Union(int S[],int root1,int root2)//并查集的合并操作(主要)
{
    if(root1==root2)
        return ;
    S[root2]=root1;
}

void Union_Optimize(int S[],int root1,int root2)//并查集的合并优化操作
{
    if(root1==root2)
        return ;
    if(S[root2]>S[root1])//root2所在树是小树,结点数少(注意是负数比较)
    {
        S[root1]+=S[root2];
        S[root2]=root1;
    }
    else//反之,roo1所在树是小树
    {
        S[root2]+=S[root1];
        S[root1]=root2;
    }
}

void Join(int S[],int x,int y)//查询并合并操作
{
    //int fx=Find(S,x),fy=Find(S,y);
    int fx=Find_Optimize(S, x),fy=Find_Optimize(S, y);
    //Union(S, fx, fy);
    Union_Optimize(S, fx, fy);
}



void Test()
{
    int UFSets[SIZE];

    Initial(UFSets);

    int n;
    // n=10;
    // Join(UFSets,6,0);
    // Join(UFSets,7,0);
    // Join(UFSets,8,0);
    // Join(UFSets,4,1);
    // Join(UFSets,9,1);


    // Join(UFSets,3,2);
    // Join(UFSets,5,2);

    n=13;
    
    UFSets[0]=-8;
    UFSets[1]=0;
    UFSets[2]=11;
    UFSets[3]=-5;
    UFSets[4]=1;
    UFSets[5]=1;
    UFSets[6]=2;
    UFSets[7]=3;
    UFSets[8]=3;
    UFSets[9]=3;
    UFSets[10]=4;
    UFSets[11]=4;  
    UFSets[12]=7;    

    for(int i=0;i<n;i++)
        cout << UFSets[i] << " ";
    cout << endl;
    
    //Join(UFSets,1,0);
    Find_Optimize(UFSets, 11);
     for(int i=0;i<n;i++)
        cout << UFSets[i] << " ";
    cout << endl;   
    
}

int main()
{
    Test();
    return 0;
}