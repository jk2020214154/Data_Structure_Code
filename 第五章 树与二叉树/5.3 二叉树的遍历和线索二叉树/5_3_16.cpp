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
}BiTNode,*BiTree,*LinkList;

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

LinkList head,pre=NULL;

LinkList Get_Leaf_List(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        Get_Leaf_List(T->lchild);//递归遍历左子树
        
        if(T->lchild==NULL&&T->rchild==NULL)
        {
            if(pre==NULL)//第一个叶子结点
                head=T,pre=T;
            else
            {
                pre->rchild=T;
                pre=T;
            }
        }

        Get_Leaf_List(T->rchild);//递归遍历右子树
    }
    return head;
}


void PrintList(LinkList L)
{
    LinkList p=L;
    while(p!=NULL)
    {
        cout << p->value << " ";
        p=p->rchild;
    }
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    InsertRightTreeNode(T->lchild, 6);
    InsertLeftTreeNode(T->rchild, 5);
    InsertRightTreeNode(T->rchild, 7);
    InsertLeftTreeNode(T->lchild->rchild, 8);
    InsertLeftTreeNode(T->lchild->rchild->lchild, 9);
    InsertRightTreeNode(T->lchild->rchild->lchild, 11);
    InsertRightTreeNode(T->rchild->lchild, 10);
    InsertRightTreeNode(T->lchild->rchild->lchild->rchild, 12);

    LinkList leaf_res=Get_Leaf_List(T);

    PrintList(leaf_res);


    //ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}