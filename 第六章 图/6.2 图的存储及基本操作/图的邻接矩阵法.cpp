#include<iostream>
#include <limits.h>

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





void Test()
{
    MGraph mg;

    cin >> mg.vexnum >> mg.arcnum;
    
/*
4 4
1234
0 1 1 0
0 0 0 0
0 0 0 1
1 0 0 0

5 5
12345
0 1 0 1 0
1 0 1 0 1
0 1 0 1 1
1 0 1 0 0
0 1 1 0 0

6 9
ABCDEF
2147483647 5 2147483647 2147483647 2147483647 2147483647
2147483647 2147483647 4 2147483647 2147483647 2147483647
8 2147483647 2147483647 2147483647 2147483647 9
2147483647 2147483647 5 2147483647 2147483647 6
2147483647 2147483647 2147483647 5 2147483647 2147483647
3 2147483647 2147483647 2147483647 1 2147483647

*/

    cin >> mg.Vex+1;
    for(int i=1;i<=mg.vexnum;i++)
        for(int j=1;j<=mg.vexnum;j++)
            cin >> mg.Edge[i][j];

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