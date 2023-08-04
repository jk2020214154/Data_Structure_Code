#include<iostream>

using namespace std;

#define MaxSize 110

typedef int ElemType;

struct TreeNode{
    ElemType value;//结点中的顺序元素
    bool isEmpty;//结点是否为空
};



void InitTree(TreeNode T[])
{
    for(int i=0;i<MaxSize;i++)
        T[i].isEmpty=true;
}


bool Search_lchild(TreeNode T[],int pos,ElemType &e)
{
    if(pos>=MaxSize||T[pos].isEmpty==true)
        return false;
    if(2*pos>=MaxSize||T[2*pos].isEmpty==true)
        return false;
    e=T[2*pos].value;
    return true;
}

bool Search_rchild(TreeNode T[],int pos,ElemType &e)
{
    if(pos>=MaxSize||T[pos].isEmpty==true)
        return false;
    if(2*pos+1>=MaxSize||T[2*pos+1].isEmpty==true)
        return false;
    e=T[2*pos+1].value;
    return true;
}

bool Search_father(TreeNode T[],int pos,ElemType &e)
{
    if(pos>=MaxSize||T[pos].isEmpty==true)
        return false;
    
    if(pos/2>=MaxSize||T[pos/2].isEmpty==true)
        return false;
    
    e=T[pos/2].value;
    return true;
}




void Test()
{
    TreeNode t[MaxSize];
    InitTree(t);

    
    t[1]={1,false};
    t[2]={2,false};
    t[3]={3,false};
    t[5]={4,false};
    t[7]={5,false};
    t[10]={6,false};
    
    /*
    编号 1 2 3 4 5 6 7 8 9 10 11
    存储 1 2 3 ^ 4 ^ 5 ^ ^ 6  ^
    */

    ElemType num1=-1,num2=-1,num3=-1;

    if(Search_lchild(t, 5, num1)==false)
        cout << "查询左孩子失败" << endl;
    else cout << "查询左孩子成功,结果为:" << num1 << endl;


    if(Search_rchild(t, 3, num2)==false)
        cout << "查询右孩子失败" << endl;
    else cout << "查询右孩子成功,结果为:" << num2 << endl;


    if(Search_father(t, 5, num3)==false)
        cout << "查询父结点失败" << endl;
    else cout << "查询父结点成功,结果为:" << num3 << endl;
}

int main()
{
    Test();
    return 0;
}