//在图或树中进行bfs

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 100010

using namespace std;

int n,m;
int head[MAXN],ed[MAXN],nex[MAXN],idx;
int dis[MAXN];

void add(int a,int b)
{
    ed[idx]=b;
    nex[idx]=head[a];
    head[a]=idx++;
}

int bfs()
{
    memset(dis,-1,sizeof(dis));
    queue<int> q;
    dis[1]=0;
    q.push(1);

    while(q.size()>0)
    {
        int temp=q.front();
        q.pop();
        for(int i=head[temp];i!=-1;i=nex[i])
        {
            int j=ed[i];
            if(dis[j]==-1)
            {
                dis[j]=dis[temp]+1;
                q.push(j);
            }
        }
    }
    return dis[n];

}

int main()
{
    memset(head,-1,sizeof(head));
    cin >> n >> m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin >> a >> b;
        add(a,b);
    }
    cout << bfs() << endl;
    return 0;
}