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

    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            b[tot++]=a[i][j];
    
    for(int i=0;i<tot;i++)
        cout << b[i] << " ";
    cout << endl;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i<=j)
                cout << b[(i-1)*(2*n-i+2)/2+j-i] << " ";
            else cout << b[(j-1)*(2*n-j+2)/2+i-j] << " ";
        }
        cout << endl;
    }
        
}

int main()
{
    Test();
    return 0;
}