#include<iostream>
#include <limits.h>

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

#define inf (INT_MAX)//无穷大

typedef char VertexType;//顶点的数据类型
typedef int EdgeType;//带权图中边上权值的数据类型

typedef struct{
    VertexType Vex[MaxVertexNum];//顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum];//邻接矩阵,边表
    int vexnum,arcnum;//图的当前顶点数,图的边数/弧数
}MGraph;

void ALGraph_To_MGraph(ALGraph g1,MGraph &g2)
{
    g2.vexnum=g1.vexnum;//更新顶点数
    g2.arcnum=g1.arcnum;//更新边数

    for(int i=1;i<=g1.vexnum;i++)//更新顶点表
        g2.Vex[i]=g1.vertices[i].data;

    for(int i=1;i<=g1.vexnum;i++)
    {
        ArcNode *p=g1.vertices[i].first;//取出第一条边

        while(p!=NULL)//遍历边链表
        {
            g2.Edge[i][p->adjvex]=1;
            p=p->next;
        }
    }
}


void Test()
{
    ALGraph alg;
    MGraph mg;

    
/*
5 7
ABCDE
0
A B
A E
B E
B C
B D
D E
C D
    
6 8
ABCDEF
1
A B
A D
D B
B E
E D
C E
C F
F F
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

    ALGraph_To_MGraph(alg,mg);

    for(int i=1;i<=mg.vexnum;i++)
    {
        cout << "顶点:" << mg.Vex[i] << " " << "到达的点:";
        for(int j=1;j<=mg.vexnum;j++)
            if(mg.Edge[i][j]!=inf&&mg.Edge[i][j]!=0)
                cout << mg.Vex[j] << " ";
        cout << endl;
    }

}

int main()
{
    Test();
    return 0;
}