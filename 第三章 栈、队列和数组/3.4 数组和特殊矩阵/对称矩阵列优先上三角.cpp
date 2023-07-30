#include<iostream>

using namespace std;

#define MAXN 110

void Test()
{
    int n=4;
    int a[5][5]={
        {0,0,0,0,0},
        {0,1,2,3,4},
        {0,2,5,6,7},
        {0,3,6,8,9},
        {0,4,7,9,6},
    };

    int b[MAXN];
    int tot=0;

    for(int j=1;j<=n;j++)
        for(int i=1;i<=j;i++)
            b[tot++]=a[i][j];
    
    for(int i=0;i<tot;i++)
        cout << b[i] << " ";
    cout << endl;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i<=j)
                cout << b[(j-1)*j/2+i-1] << " ";
            else cout << b[(i-1)*i/2+j-1] << " ";
        }
        cout << endl;
    }
        
}

int main()
{
    Test();
    return 0;
}