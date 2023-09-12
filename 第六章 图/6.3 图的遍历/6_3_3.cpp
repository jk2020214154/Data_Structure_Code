#include<iostream>
#include<limits.h>
#include<stack>

using namespace std;

#define MaxVertexNum 100//顶点数目的最大值

typedef char VertexType;//顶点的数据类型
typedef int InfoType;//带权图中边上权值的数据类型

typedef struct ArcNode{//边表结点
    int adjvex;//该弧所指向的顶点的位置
    struct ArcNode *next;//指向下一条弧的指针
    //InfoType info;//网的边权值
}ArcNode;

typedef struct VNode{//顶点表结点
    VertexType data;//顶点信息
    ArcNode *first;//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MaxVertexNum];

typedef struct{//邻接表
    AdjList vertices;//邻接表
    int vexnum,arcnum;//图的当前顶点数,图的边数/弧数
}ALGraph;

int GetGraphIndex(ALGraph g,VertexType value)
{
    for(int i=1;i<=g.vexnum;i++)
        if(g.vertices[i].data==value)
            return i;
    return -1;
}

int FirstNeighbor(ALGraph G,int x)
{
    if(x>=1&&x<=G.vexnum)
    {
        if(G.vertices[x].first!=NULL)
            return G.vertices[x].first->adjvex;
    }
    return -1;
}

int NextNeighbor(ALGraph G,int x,int y)
{
    ArcNode *temp=G.vertices[x].first;

    while(temp!=NULL)
    {
        if(temp->adjvex==y)
            break;
        temp=temp->next;
    }

    if(temp==NULL||temp->next==NULL)
        return -1;
    else return temp->next->adjvex;
}

bool visited[MaxVertexNum];

void visit(ALGraph G,int pos)
{
    cout << G.vertices[pos].data << " ";
}


void DFS(ALGraph G,int start)
{
    stack<int> sta;
    sta.push(start);//把起点放入栈中
    visited[start]=true;

    while(sta.size()>0)
    {
        int temp=sta.top();//取出栈顶元素
        visit(G,temp);
        sta.pop();
        for(int j=FirstNeighbor(G, temp);j!=-1;j=NextNeighbor(G, temp, j))//访问其未被访问的邻接顶点
            if(visited[j]==false)
            {
                sta.push(j);
                visited[j]=true;//标记,防止再次入栈
            }        
    }    
}

void DFSTraverse(ALGraph G)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    
    for(int i=1;i<=G.vexnum;i++)
        if(visited[i]==false)
            DFS(G,i);
}


void Test()
{
    ALGraph alg;
    
/*
8 10
12345678
0
1 2
1 5
2 6
3 4
3 6
3 7
4 7
4 8
6 7
7 8

8 7
ABCDEFGH
0
A B
A C
B D
B E
C F
C G
E H
*/

    cin >> alg.vexnum >> alg.arcnum;

    for(int i=1;i<=alg.vexnum;i++)
    {
        cin >> alg.vertices[i].data;
        alg.vertices[i].first=NULL;
    }

    int type;//1表示有向图,0表示无向图
    cin >> type;
    
    for(int i=1;i<=alg.arcnum;i++)
    {
        VertexType a,b;
        cin >> a >> b;
        int index_a=GetGraphIndex(alg, a);
        int index_b=GetGraphIndex(alg, b);

        //cout << index_a << " " << index_b << endl;

        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));

        p1->adjvex=index_b;
        p1->next=alg.vertices[index_a].first;//头插法插入
        alg.vertices[index_a].first=p1;

        if(type==0)//无向图,反向建边
        {
            ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));

            p2->adjvex=index_a;
            p2->next=alg.vertices[index_b].first;//头插法插入
            alg.vertices[index_b].first=p2;            
        }
    }

    for(int i=1;i<=alg.vexnum;i++)
    {
        cout << "顶点:" << alg.vertices[i].data << " " << "到达的点:";
        
        
        for(int j=FirstNeighbor(alg, i);j!=-1;j=NextNeighbor(alg, i, j))
            cout << alg.vertices[j].data << " ";
        cout << endl;
    }

    DFSTraverse(alg);

}

int main()
{
    Test();
    return 0;
}