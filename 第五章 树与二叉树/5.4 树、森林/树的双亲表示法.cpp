#include<iostream>

using namespace std;

#define MAX_TREE_SIZE 100
typedef int ElemType;

typedef struct
{//树的结点定义
    ElemType data;//数据元素
    int parent;//双亲位置域
}PTNode;

typedef struct
{
    PTNode nodes[MAX_TREE_SIZE];//双亲表示
    int size;//结点个数
}PTree;

void Find_Parent(PTree p,ElemType e)
{
    for(int i=0;i<p.size;i++)
    {
        if(p.nodes[i].data==e)
        { 
        
            int fa=p.nodes[i].parent;
            if(fa==-1)
                cout << "该点为根结点" << endl;
            else
            {
                cout << "父结点位置:" << fa << endl;
                cout << "父结点的值:" << p.nodes[fa].data << endl;
            }
            return ;
        }
    }

    cout << "查询失败" << endl;
}

void Test()
{
    PTree pt;

    int n;
    cin >> n;
    
    pt.size=n;
    for(int i=0;i<=n-1;i++)
        cin >> pt.nodes[i].data >> pt.nodes[i].parent;
    /*
    10
    9 -1
    8 0
    7 0
    6 0
    5 1
    4 1
    3 3
    2 6
    1 6 
    0 6 
    */
    Find_Parent(pt, 8);
}

int main()
{
    Test();
    return 0;
}