#include<iostream>
#include<stack>
#include<queue>

using namespace std;

#define MaxSize 110

typedef int ElemType;

typedef struct BiTNode{
    ElemType weight;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
    //struct BiTNode *parent;
}BiTNode,*BiTree;

void InitTree(BiTree &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(BiTree)malloc(sizeof(BiTree));

    T->weight=0;
    T->lchild=NULL;
    T->rchild=NULL;
}

bool InsertLeftTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->weight=e;
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
    p->weight=e;
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

typedef struct QueueNode{
    BiTNode *bitnode;
    int level;
}QueueNode;

int Calc_Wpl(BiTree T)
{
    int wpl_res=0;

    if(T==NULL)
        return 0;
    
    queue<QueueNode> q;//此处为了方便使用c++中的stl
    QueueNode temp={T,1};
    q.push(temp);//将根结点入队


    while(q.empty()==0)
    {
        QueueNode new_node=q.front();//队头结点出队
        q.pop();

        if(new_node.bitnode->lchild==NULL&&new_node.bitnode->rchild==NULL)
            wpl_res+=(new_node.level-1)*new_node.bitnode->weight;

        if(new_node.bitnode->lchild!=NULL)//左子树不空,将左子树根结点入队
        {
            temp.bitnode=new_node.bitnode->lchild;
            temp.level=new_node.level+1;
            q.push(temp);
        }
        
        if(new_node.bitnode->rchild!=NULL)//右子树不空,将右子树根结点入队
        {
            temp.bitnode=new_node.bitnode->rchild;
            temp.level=new_node.level+1;
            q.push(temp);
        }
    }
    return wpl_res;
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 0);
    InsertRightTreeNode(T, 9);
    InsertLeftTreeNode(T->lchild, 0);
    InsertRightTreeNode(T->lchild, 5);
    InsertLeftTreeNode(T->lchild->lchild, 0);
    InsertRightTreeNode(T->lchild->lchild, 2);
    InsertLeftTreeNode(T->lchild->lchild->lchild, 1);
    InsertRightTreeNode(T->lchild->lchild->lchild, 2);


    cout << Calc_Wpl(T) << endl;

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}