#include<iostream>

using namespace std;

#define MaxLen 255

typedef struct {
    char ch[MaxLen+1];
    //存储串的一维数组,ch[0]~ch[255],共256个;
    //通常情况下 ch[0]存放串的长度,或者闲置不用,真正串的内容从ch[1]开始
    int length;
}SString;


void StrAssign(SString &Str,char str[])//赋值操作
{
    int len=0;
    while(str[len]!='\0')
        len++;
    Str.length=len;

    if(len>MaxLen)
        cout << "赋值失败" << endl;
    else
    {
        for(int i=1;i<=Str.length;i++)//注意时从 ch[1]开始
            Str.ch[i]=str[i-1];       
    }
}

bool StrEmpty(SString Str)//判空操作
{
    return Str.length==0;
}

int StrLength(SString Str)//求串长
{
    return Str.length;
}

void PrintSString(SString Str)
{
    if(Str.length==0)
        cout << "该串为空" << endl;
    else
    {
        for(int i=1;i<=Str.length;i++)
            cout << Str.ch[i];
        cout << endl;       
    }
}

int StrIndex(SString Str1,SString Str2)//定位操作
{
    int i=1,j=1;//分别指向Str1和Str2的第一个元素
    while(i<=Str1.length&&j<=Str2.length)
    {
        if(Str1.ch[i]==Str2.ch[j])
            i++,j++;
        else i=i-j+2,j=1;
    }
    if(j>Str2.length)
        return i-Str2.length;
    else return 0;
}


void Test()
{
    SString s1,s2;

    char str1[]="ababcabcacbab";
    char str2[]="abcac";

    StrAssign(s1, str1);
    StrAssign(s2, str2);
    
    PrintSString(s1);
    PrintSString(s2);
    
    cout << StrIndex(s1,s2) << endl;
   
}

int main()
{
    Test();
    return 0;
}