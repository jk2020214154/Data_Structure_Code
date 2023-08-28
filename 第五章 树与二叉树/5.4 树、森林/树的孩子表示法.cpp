#include <cstdlib>
#include<iostream>

using namespace std;

#define MAX_TREE_SIZE 100
typedef char ElemType;

struct ChildNode
{//链表中每个结点的定义
    //链表中每个结点存储的不是数据本身,而是数据在数组中存储的位置下标
    int child;//孩子结点在数组中的位置
    struct ChildNode *next;//下一个孩子
};

typedef struct
{//树中每个结点的定义
    ElemType data;
    ChildNode *firstchild;//孩子链表头指针
}CHNode;

typedef struct
{
    CHNode nodes[MAX_TREE_SIZE];
    int size;
}CTree;


void Find_Kids(CTree t,ElemType e)
{
    for(int i=0;i<t.size;i++)
    {
        if(t.nodes[i].data==e)
        {
            ChildNode *p=t.nodes[i].firstchild->next;

            if(p==NULL)
                cout << "该结点为叶子结点" << endl;
            else
            {
                while(p!=NULL)
                {
                    cout << t.nodes[p->child].data << " ";
                    p=p->next;
                }
                cout << endl;
            }
            return ;
        }
    }

    cout << "该结点不存在" << endl;
}

void Test()
{
    CTree ct;
    int n;

    cin >> n;

    ct.size=n;

    for(int i=0;i<ct.size;i++)
    {
        getchar();
        cin >> ct.nodes[i].data;

        ct.nodes[i].firstchild=(ChildNode *)malloc(sizeof(ChildNode));
        ct.nodes[i].firstchild->next=NULL;

        int num;
        cin >> num;//输入当前结点的孩子结点个数

        ChildNode *p=ct.nodes[i].firstchild;//采用尾插法插入(需要尾指针)
        for(int j=1;j<=num;j++)
        {
            ChildNode *q=(ChildNode *)malloc(sizeof(ChildNode));
            cin >> q->child;

            q->next=NULL;
            p->next=q;
            p=p->next;
        }
    }
    
/*
10
R 3 1 2 3
A 2 4 5
B 0
C 1 6
D 0
E 0
F 3 7 8 9
G 0
H 0
K 0
*/
    Find_Kids(ct, 'R');
    Find_Kids(ct, 'A');
    Find_Kids(ct, 'B');
    Find_Kids(ct, 'C');
    Find_Kids(ct, 'D');
    Find_Kids(ct, 'E');
    Find_Kids(ct, 'F');
    Find_Kids(ct, 'G');
    Find_Kids(ct, 'H');
    Find_Kids(ct, 'I');//不存在
    Find_Kids(ct, 'K');
}

int main()
{
    Test();
    return 0;
}