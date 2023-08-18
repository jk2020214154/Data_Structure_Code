#include<iostream>
#include<stack>
#include<queue>

using namespace std;

#define MaxSize 110

typedef int ElemType;

typedef struct BiTNode{
    ElemType value;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
    //struct BiTNode *parent;
}BiTNode,*BiTree;

void InitTree(BiTree &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(BiTree)malloc(sizeof(BiTree));

    T->value=1;
    T->lchild=NULL;
    T->rchild=NULL;
}

bool InsertLeftTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    T->lchild=p;
    return true;
}

bool InsertRightTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    T->rchild=p;
    return true;    
}

void ReleaseTree(BiTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->lchild);
    	ReleaseTree(t->rchild);
    	free(t);
  	}
}

void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
}



void PreOrder(BiTree T)//前序遍历
{
    if(T!=NULL)
    {
        visit(T);//访问根节点
        PreOrder(T->lchild);//递归遍历左子树
        PreOrder(T->rchild);//递归遍历右子树
    }
}

bool isSimilar(BiTree T1,BiTree T2)
{
    if(T1==NULL&&T2==NULL)//均为空
        return true;
    else if(T1==NULL||T2==NULL)//有一个树为空另一个树不空
        return false;
    else
    {
        bool left_sim=isSimilar(T1->lchild, T2->lchild);//左子树相似
        bool right_sim=isSimilar(T1->rchild, T2->rchild);//右子树相似
        return left_sim&&right_sim;//两者都成立时相似
    }
}


void Test()
{
    BiTree T1,T2;
    InitTree(T1);
    InitTree(T2);
    InsertLeftTreeNode(T1, 2);
    InsertRightTreeNode(T1, 3);
    InsertLeftTreeNode(T1->lchild, 4);
    InsertRightTreeNode(T1->lchild, 6);
    InsertLeftTreeNode(T1->rchild, 5);
    InsertRightTreeNode(T1->rchild, 7);
    InsertLeftTreeNode(T1->lchild->rchild, 8);
    InsertLeftTreeNode(T1->lchild->rchild->lchild, 9);
    InsertRightTreeNode(T1->lchild->rchild->lchild, 11);
    InsertRightTreeNode(T1->rchild->lchild, 10);
    InsertRightTreeNode(T1->lchild->rchild->lchild->rchild, 12);

    InsertLeftTreeNode(T2, 2);
    InsertRightTreeNode(T2, 3);
    InsertLeftTreeNode(T2->lchild, 4);
    InsertRightTreeNode(T2->lchild, 6);
    InsertLeftTreeNode(T2->rchild, 33);
    InsertRightTreeNode(T2->rchild, 7);
    InsertLeftTreeNode(T2->lchild->rchild, 8);
    InsertLeftTreeNode(T2->lchild->rchild->lchild, 9);
    InsertRightTreeNode(T2->lchild->rchild->lchild, 11);
    //InsertRightTreeNode(T2->rchild->lchild, 10);
    InsertRightTreeNode(T2->lchild->rchild->lchild->rchild, 12);
    
    
    

    if(isSimilar(T1, T2)==true)
        cout << "相似" << endl;
    else cout << "不相似" << endl;

    ReleaseTree(T1);
    ReleaseTree(T2);
}

int main()
{
    Test();
    return 0;
}