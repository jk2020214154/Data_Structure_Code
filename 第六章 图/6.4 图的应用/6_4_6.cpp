#include<iostream>
#include<limits.h>

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


int vis[MaxVertexNum];//1代表正在访问,-1代表访问结束,0代表未访问
int ans[MaxVertexNum],tot;


bool dfs_topsort(ALGraph G,int root)
{
    vis[root]=1;//正在访问
    for(int j=FirstNeighbor(G, root);j!=-1;j=NextNeighbor(G, root, j))
    {
        if(vis[j]==1)//如果后继比前驱先访问,说明存在环
            return false;
        if(vis[j]==0&&dfs_topsort(G, j)==false)//如果后继未被访问,访问后继返回假,也是失败
            return false;
    }

    vis[root]=-1;
    ans[tot++]=root;//在递归结束才加入拓扑序列数组中,最深层次先返回
    return true;
}


void Test()
{
    ALGraph alg;

    /*
5 7
ABCDE
A B
A D
B D
B C
D C
D E
C E

A B D C E 

7 9
ABCDEFG
A B
B C
B D
C F
C E
D E
D G
E G
F G    

A B C F D E G 

    
    */

    cin >> alg.vexnum >> alg.arcnum;

    for(int i=1;i<=alg.vexnum;i++)
    {
        cin >> alg.vertices[i].data;
        alg.vertices[i].first=NULL;
    }

    // int type;//1表示有向图,0表示无向图
    // cin >> type;
    
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

        // if(type==0)//无向图,反向建边
        // {
        //     ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));

        //     p2->adjvex=index_a;
        //     p2->next=alg.vertices[index_b].first;//头插法插入
        //     alg.vertices[index_b].first=p2;            
        // }
    }

    for(int i=1;i<=alg.vexnum;i++)
        if(vis[i]==0)
            dfs_topsort(alg,i);
    for(int i=tot-1;i>=0;i--)
        cout << alg.vertices[ans[i]].data << " ";
    cout << endl;
}

int main()
{
    Test();
    return 0;
}