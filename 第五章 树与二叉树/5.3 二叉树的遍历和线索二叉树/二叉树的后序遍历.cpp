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

void PostOrder(BiTree T)//后序遍历
{
    if(T!=NULL)
    {
        PostOrder(T->lchild);//递归遍历左子树
        PostOrder(T->rchild);//递归遍历右子树
        visit(T);//访问根结点
    }
}

typedef struct StackNode{
    BiTNode *bitnode;
    bool isFirst;
}StackNode;

void PostOrder_Non_Recursive1(BiTree T)//后序遍历非递归
{
    stack<StackNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            StackNode *new_node=(StackNode *)malloc(sizeof(StackNode));
            new_node->bitnode=p;
            new_node->isFirst=true;//标记第一次访问
            
            //s.push(p);//当前结点入栈
            s.push(new_node);

            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            StackNode *temp_node=s.top();//获取栈顶
            s.pop();//栈顶元素出栈

            if(temp_node->isFirst==true)//表示是第一次出现在栈顶(从左子树返回)
            {
                temp_node->isFirst=false;
                s.push(temp_node);
                p=temp_node->bitnode->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
            }
            else//第二次出现在栈顶 
            {
                visit(temp_node->bitnode);// ***访问当前结点***
                p=NULL;//结点访问完后,重置p指针
            }
        }
    }
}


void PostOrder_Non_Recursive2(BiTree T)//后序遍历非递归
{
    stack<BiTNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;
    BiTNode *pre=NULL;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            s.push(p);//当前结点入栈
            p=p->lchild;//左孩子不空,一直向左走
        }
        else//向右
        {
            p=s.top();//获取栈顶
            if(p->rchild!=NULL&&p->rchild!=pre)//若右子树存在,且未被访问
                p=p->rchild;//转向右
            else//否则,弹出结点并访问
            {
                s.pop();
                visit(p);// ***访问当前结点***
                pre=p;
                p=NULL;//结点访问完,重置p指针
            }
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

    cout << "递归后序遍历结果:";
    PostOrder(T);
    cout << endl << "非递归后序遍历结果:";
    PostOrder_Non_Recursive1(T);
    cout << endl << "非递归后序遍历结果:";
    PostOrder_Non_Recursive2(T);

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}