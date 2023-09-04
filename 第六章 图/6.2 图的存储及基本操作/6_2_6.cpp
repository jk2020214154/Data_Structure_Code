#include<iostream>
#include <limits.h>

using namespace std;

#define MAXV 100//顶点数目的最大值
#define inf (INT_MAX)//无穷大

typedef char VertexType;//顶点的数据类型
typedef int EdgeType;//带权图中边上权值的数据类型

typedef struct {                    // 图的定义
    int numVertices, numEdges;      // 图中实际的顶点数和边数
    char VerticesList[MAXV];        // 顶点表，MAXV为已定义常量
    int Edge[MAXV][MAXV];           // 邻接矩阵
}MGraph;


// int IsExistEL(MGraph G)
// {
//     int degree[MAXV];
//     for(int i=1;i<=G.numVertices;i++)//初始化置0
//         degree[i]=0;
    
//     for(int i=1;i<=G.numVertices;i++)//遍历无向图统计所有点的度
//         for(int j=1;j<=G.numVertices;j++)
//             degree[i]+=G.Edge[i][j];
    
//     int tot=0;//遍历degree数组统计度为奇数的点的个数
//     for(int i=1;i<=G.numVertices;i++)
//         if(degree[i]%2==1)
//             tot++;
//     //检查度为奇数的点个数是否为0或者2
//     if(tot==0||tot==2)//存在EL路径
//         return 1;
//     return 0;//存在EL路径
// }


int IsExistEL(MGraph G)
{
    int tot=0;
    for(int i=1;i<=G.numVertices;i++)//遍历无向图统计所有点的度
    {
        int degree=0;
        for(int j=1;j<=G.numVertices;j++)
            degree+=G.Edge[i][j];
        if(degree%2==1)//统计度为奇数的点的个数
            tot++;
    }
    //检查度为奇数的点个数是否为0或者2
    if(tot==0||tot==2)//存在EL路径
        return 1;
    return 0;//存在EL路径
}


void Test()
{
    MGraph mg;

    cin >> mg.numVertices >> mg.numEdges;
    
/*
5 5
12345
0 1 0 1 0
1 0 1 0 1
0 1 0 1 1
1 0 1 0 0
0 1 1 0 0

4 3
ABCD
0 1 1 1
1 0 0 0
1 0 0 0
1 0 0 0
*/

    cin >> mg.VerticesList+1;
    for(int i=1;i<=mg.numVertices;i++)
        for(int j=1;j<=mg.numVertices;j++)
            cin >> mg.Edge[i][j];

    // for(int i=1;i<=mg.numVertices;i++)
    // {
    //     cout << "顶点:" << mg.VerticesList[i] << " " << "到达的点:";
    //     for(int j=1;j<=mg.numVertices;j++)
    //         if(mg.Edge[i][j]!=inf&&mg.Edge[i][j]!=0)
    //             cout << mg.VerticesList[j] << " ";
    //     cout << endl;
    // }

    if(IsExistEL(mg)==1)
        cout << "存在欧拉路径" << endl;
    else cout  << "不存在欧拉路径" << endl;    
}

int main()
{
    Test();
    return 0;
}