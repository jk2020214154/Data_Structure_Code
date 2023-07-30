#include<iostream>

using namespace std;

#define MAXN 110

void Test()
{
    int n=5;
    int a[6][6]={
        {0,0,0,0,0,0},
        {0,1,2,0,0,0},
        {0,3,4,5,0,0},
        {0,0,6,7,8,0},
        {0,0,0,9,10,11},
        {0,0,0,0,12,13},
    };

    int b[MAXN];
    int tot=0;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(abs(i-j)<=1)
                b[tot++]=a[i][j];
    
    for(int i=0;i<tot;i++)
        cout << b[i] << " ";
    cout << endl;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(abs(i-j)<=1)
                cout << b[2*i+j-3] << " ";
            else cout << 0 << " ";
        }
        cout << endl;
    }
 
    for(int pos=0;pos<tot;pos++)
    {
        int i=(pos+1)/3+1;
        int j=pos-2*i+3;
        
        cout << i << " " << j << " " << a[i][j] << endl; 
    }
        
}

int main()
{
    Test();
    return 0;
}