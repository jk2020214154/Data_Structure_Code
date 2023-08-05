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

bool Search_Common_Ancestor(TreeNode T[],int i,int j,ElemType &e)
{
    if(T[i].isEmpty!=true&&T[j].isEmpty!=true)
    {
        while(i!=j)
        {
            if(i>j)
                i/=2;
            else j/=2;
        }
        e=T[i].value;
        return true;
    }

    return false;
}


void Test()
{
    TreeNode t[MaxSize];
    InitTree(t);

    
    t[1]={1,false};
    t[2]={2,false};
    t[3]={3,false};
    t[4]={4,false};
    t[5]={5,false};
    t[6]={6,false};
    t[7]={7,false};
    t[8]={8,false};
    t[9]={9,false};
    t[10]={10,false};
    t[11]={11,false};
    t[12]={12,false};


    ElemType num=-1;
    if(Search_Common_Ancestor(t, 12, 7, num)==false)
        cout << "查询失败" << endl;
    else cout << num << endl;
    
}

int main()
{
    Test();
    return 0;
}