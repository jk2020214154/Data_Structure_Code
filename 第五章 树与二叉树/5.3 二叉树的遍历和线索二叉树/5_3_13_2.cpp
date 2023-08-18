#include<iostream>
#include<stack>
#include<queue>
#include<vector>

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


void InOrder(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        InOrder(T->rchild);//递归遍历右子树
    }
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

int treeDepth(BiTree T)
{
    if(T==NULL)
        return 0;
    else
    {
        int l=treeDepth(T->lchild);
        int r=treeDepth(T->rchild);
        return l>r?l+1:r+1;
    }
}

typedef struct StackNode{
    BiTNode *bitnode;
    bool isFirst;
}StackNode;

//此处设p1在p2左边
BiTNode* Search_Common_Ancestor(BiTree T,BiTNode *p1,BiTNode *p2)
{
    if(p1==p2)
        return p1;
    stack<StackNode* > s;//此处为了方便使用c++中的stl

    stack<StackNode* > temp1,temp2;//存储两个的祖先的栈

    vector<BiTNode*> v1,v2;//分别存储各自的祖先

    int flag=0;//标记是否经过p
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
            if(flag==0)
                temp1.push(new_node);
            temp2.push(new_node);

            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            
            StackNode *temp_node=s.top();//获取栈顶
            s.pop();//栈顶元素出栈
            if(flag==0)
                temp1.pop();
            temp2.pop();

            if(temp_node->isFirst==true)//表示是第一次出现在栈顶(从左子树返回)
            {
                temp_node->isFirst=false;
                s.push(temp_node);
                if(flag==0)
                    temp1.push(temp_node);
                temp2.push(temp_node);

                p=temp_node->bitnode->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
            }
            else//第二次出现在栈顶 
            {
                if(temp_node->bitnode==p1)
                {
                    flag=1;
                    while(temp1.size()>0)
                        v1.push_back(temp1.top()->bitnode),temp1.pop();
                }
                
                if(temp_node->bitnode==p2)
                {
                    while(temp2.size()>0)
                        v2.push_back(temp2.top()->bitnode),temp2.pop();                    
                    // for(int i=0;i<v1.size();i++)
                        // cout << v1[i]->value << " ";
                    // cout << endl;
                    // for(int i=0;i<v2.size();i++)
                        // cout << v2[i]-> value << " ";
                    // cout << endl;
                    for(int i=0;i<v1.size();i++)
                        for(int j=0;j<v2.size();j++)
                            if(v1[i]==v2[j])
                                return v1[i];
                }
                p=NULL;//结点访问完后,重置p指针
            }
        }
    }
    return NULL;
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


    BiTNode* p=Search_Common_Ancestor(T,T->lchild->lchild , T->lchild->rchild->lchild->rchild);
    
    //p=Search_Common_Ancestor(T, T->lchild->rchild, T->rchild->lchild);
    
    //p=Search_Common_Ancestor(T, T->lchild->rchild, T->lchild->rchild);
    
    if(p!=NULL)
        cout << p->value << endl;
    else cout << "NULL" << endl;
    
    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}