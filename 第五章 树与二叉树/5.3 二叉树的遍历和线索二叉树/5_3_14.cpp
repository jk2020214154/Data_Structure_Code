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

typedef struct QueueNode{
    BiTNode *bitnode;
    int level;
}QueueNode;


int Calc_Width(BiTree T)//层次遍历
{
    if(T==NULL)
        return 0;
    
    queue<QueueNode> q;//此处为了方便使用c++中的stl
    QueueNode temp={T,1};
    q.push(temp);//将根结点入队

    int last=0,maxx=0;//记录上一层

    int tot=0;

    while(q.empty()==0)
    {
        QueueNode new_node=q.front();//队头结点出队
        q.pop();
        
    
        if(last!=new_node.level)//更新上一层的最大值
        {
            if(tot>maxx)
                maxx=tot;
            tot=1;
            last=new_node.level;
        }
        else tot++;

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

    maxx=max(maxx,tot);
    return maxx;
}

void LevelOrder(BiTree T)//层次遍历
{
    queue<BiTNode *> q;//此处为了方便使用c++中的stl

    q.push(T);//将根结点入队

    while(q.empty()==0)
    {
        BiTNode *p=q.front();//队头结点出队
        q.pop();
        visit(p);//访问队头元素

        if(p->lchild!=NULL)//左子树不空,将左子树根结点入队
            q.push(p->lchild);
        if(p->rchild!=NULL)//右子树不空,将右子树根结点入队
            q.push(p->rchild);
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


    cout << "最大宽度:" << endl << Calc_Width(T);
    
    cout << endl <<  "层次遍历结果:";
    LevelOrder(T);
    
    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}