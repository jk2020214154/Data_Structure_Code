#include<iostream>
#include<limits.h>
#include<queue>

using namespace std;

#define MaxVertexNum 100//顶点数目的最大值
#define inf (INT_MAX)//无穷大

typedef char VertexType;//顶点的数据类型
typedef int EdgeType;//带权图中边上权值的数据类型

typedef struct{
    VertexType Vex[MaxVertexNum];//顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum];//邻接矩阵,边表
    int vexnum,arcnum;//图的当前顶点数,图的边数/弧数
}MGraph;

int FirstNeighbor(MGraph G,int x)
{
    if(x>=1&&x<=G.vexnum)
    {
        for(int i=1;i<=G.vexnum;i++)
            if(G.Edge[x][i]!=inf&&G.Edge[x][i]!=0)
                return i;
    }
    return -1;
}

int NextNeighbor(MGraph G,int x,int y)
{
    if(x>=1&&x<=G.vexnum&&y>=1&&y<=G.vexnum)
    {
        for(int i=y+1;i<=G.vexnum;i++)
            if(G.Edge[x][i]!=inf&&G.Edge[x][i]!=0)
                return i;
    }
    return -1;
}


bool visited[MaxVertexNum];

void visit(MGraph G,int pos)
{
    cout << G.Vex[pos] << " ";
}

void BFS(MGraph G,int start)
{
    queue<int> q;//此处为了方便,使用C++的stl中的队列

    //将起点放入队列中,并标记为true
    q.push(start);
    visited[start]=true;

    while(q.size()>0)
    {
        int temp=q.front();
        visit(G,temp);//访问该结点
        q.pop();//弹出队列

        for(int j=FirstNeighbor(G, temp);j!=-1;j=NextNeighbor(G, temp, j))
        {
            if(visited[j]==false)//当前邻接顶点未访问,放入队列并标记
            {
                q.push(j);
                visited[j]=true;
            }
        }
    }
    cout << endl << "--------" << endl;//观察使用 BFS次数
}

void BFSTraverse(MGraph G)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    
    for(int i=1;i<=G.vexnum;i++)
        if(visited[i]==false)
            BFS(G,i);
}

void Test()
{
    MGraph mg;

    cin >> mg.vexnum >> mg.arcnum;
    
/*
8 10
12345678
0 0 0 0 1 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 
0 0 1 0 0 0 1 0
0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0
0 0 1 0 0 1 0 1
0 0 0 1 0 0 0 0

8 7
ABCDEFGH
0 1 1 0 0 0 0 0
1 0 0 1 1 0 0 0
1 0 0 0 0 1 1 0
0 1 0 0 0 0 0 0
0 1 0 0 0 0 0 1
0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0

*/

    cin >> mg.Vex+1;
    for(int i=1;i<=mg.vexnum;i++)
        for(int j=1;j<=mg.vexnum;j++)
            cin >> mg.Edge[i][j];

    for(int i=1;i<=mg.vexnum;i++)
    {
        cout << "顶点:" << mg.Vex[i] << " " << "到达的点:";
        for(int j=FirstNeighbor(mg, i);j!=-1;j=NextNeighbor(mg, i, j))
                cout << mg.Vex[j] << " ";
        cout << endl;
    }

    BFSTraverse(mg);

}

int main()
{
    Test();
    return 0;
}