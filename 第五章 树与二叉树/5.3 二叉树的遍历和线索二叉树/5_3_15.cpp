#include<iostream>

using namespace std;

#define MaxSize 110

typedef int ElemType;

void Pre_To_Post(ElemType pre[],ElemType post[],int l1,int r1,int l2,int r2)
{
    if(l1<=r1)
    {
        post[r2]=pre[l1];//先序的第一个元素是后序最后一个元素
        int mid=(r1-l1)/2;
        Pre_To_Post(pre, post, l1+1, l1+mid, l2, l2+mid-1);//左子树
        //左子树元素个数为mid-1(刨去根)
        Pre_To_Post(pre, post, l1+mid+1, r1, l2+mid, r2-1);//右子树
        //后序最后一个元素被占据
    }
}


void Test()
{
    ElemType pre[MaxSize],post[MaxSize];

    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> pre[i];

    /*
    前面为先序,后面为后序
    7
    1 2 3 4 5 6 7
    3 4 2 6 7 5 1 
    
    15
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    4 5 3 7 8 6 2 11 12 10 14 15 13 9 1 


    */

    Pre_To_Post(pre, post, 1, n, 1, n);
    
    for(int i=1;i<=n;i++)
        cout << post[i] << " ";
    
    cout << endl;

}


int main()
{  
    Test();
    return 0;
}