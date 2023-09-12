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
VertexType path[MaxVertexNum];

void DFS(ALGraph G,int start_,int end_,int tot)
{
    visited[start_]=true;
    path[tot]=G.vertices[start_].data;
    if(start_==end_)
    {
        for(int i=0;i<=tot;i++)
            cout << path[i] << " ";
        cout << endl;
        visited[start_]=false;
        return ;
    }

    for(int j=FirstNeighbor(G, start_);j!=-1;j=NextNeighbor(G, start_, j))
        if(visited[j]==false)
            DFS(G,j,end_,tot+1);
    visited[start_]=false;
}

void DFSTraverse(ALGraph G,int start_,int end_)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    DFS(G, start_, end_, 0);
}

/*
bool visited[MaxVertexNum];

void DFS(ALGraph G,int start_,int end_,vector<VertexType> &path)
{
    
    //cout << start_ << " " << end_ << endl;
    if(start_==end_)
    {
        for(int i=0;i<path.size();i++)
            cout << G.vertices[path[i]].data << " ";
        cout << endl;
        return ;
    }

    for(int j=FirstNeighbor(G, start_);j!=-1;j=NextNeighbor(G, start_, j))
    {
        if(visited[j]==false)
        {
            visited[j]=true;
            path.push_back(j);
            DFS(G, j, end_, path);
            path.pop_back();
            visited[j]=false;
        }
    }
}

void DFSTraverse(ALGraph G,int start_,int end_)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    vector<VertexType> path;
    path.push_back(start_);
    visited[start_]=true;
    DFS(G, start_, end_,path);
    path.pop_back();
    visited[start_]=false;
}

*/

void Test()
{
    ALGraph alg;
    
/*
8 8
12345678
1
1 2
1 3
2 4 
3 4
4 5
5 3
2 7
7 4
1 4

8 8
12345678
1
1 2
1 3
2 4 
3 4
4 5
5 3
2 7
7 4
2 5

8 8
12345678
1
1 2
1 3
2 4 
3 4
4 5
5 3
2 7
7 4
1 5
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

    int start_,end_;
    cin >> start_ >> end_;

    DFSTraverse(alg,start_,end_);
}

int main()
{
    Test();
    return 0;
}