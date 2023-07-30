#include<iostream>

using namespace std;

#define MAXN 110

void Test()
{
    int n=4;
    int a[5][5]={
        {0,0,0,0,0},
        {0,1,2,3,4},
        {0,11,5,6,7},
        {0,11,11,8,9},
        {0,11,11,11,6},
    };

    int b[MAXN];
    int tot=0;

    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            b[tot++]=a[i][j];
    b[tot++]=a[2][1];
    
    for(int i=0;i<tot;i++)
        cout << b[i] << " ";
    cout << endl;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i<=j)
                cout << b[(i-1)*(2*n-i+2)/2+j-i] << " ";
            else cout << b[n*(n+1)/2] << " ";
        }
        cout << endl;
    }
        
}

int main()
{
    Test();
    return 0;
}