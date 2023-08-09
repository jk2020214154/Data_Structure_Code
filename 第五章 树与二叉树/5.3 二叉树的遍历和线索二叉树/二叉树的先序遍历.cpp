#include<iostream>
#include<stack>

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

void PreOrder_Non_Recursive(BiTree T)//前序遍历非递归
{
    stack<BiTNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            visit(p);// ***访问当前结点***
            s.push(p);//当前结点入栈
            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            p=s.top();//获取栈顶
            s.pop();//栈顶元素出栈

            p=p->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
        }
    }
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    InsertRightTreeNode(T->lchild, 5);
    InsertLeftTreeNode(T->rchild, 6);
    InsertRightTreeNode(T->rchild, 7);

    cout << "递归前序遍历结果:";
    PreOrder(T);
    cout << endl << "非递归前序遍历结果:";
    PreOrder(T);


    ReleaseTree(T);

}

int main()
{
    Test();
    return 0;
}