#include<iostream>
#include<limits.h>

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

void DFS(MGraph G,int start,int &node_num,int &edge_num)
{
    visited[start]=true;//标记该点,并增加顶点的个数
    node_num++;

    for(int j=FirstNeighbor(G, start);j!=-1;j=NextNeighbor(G, start, j))
    {
        //边数+1
        edge_num++;
        if(visited[j]==false)
            DFS(G,j,node_num,edge_num);
    }
}

bool isTree(MGraph G)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    int node_num=0,edge_num=0;

    DFS(G,1,node_num,edge_num);

    if(node_num==G.vexnum&&edge_num==2*(G.vexnum-1))
        return true;
    return false;
}

void Test()
{
    MGraph mg;

    cin >> mg.vexnum >> mg.arcnum;
    
/*
5 6
12345
0 1 0 1 0
1 0 1 0 1
0 1 0 1 1
1 0 1 0 0
0 1 1 0 0

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

    if(isTree(mg)==true)
        cout << "该图是一个树" << endl;
    else cout << "该图不是一个树" << endl;
}

int main()
{
    Test();
    return 0;
}