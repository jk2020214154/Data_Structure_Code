
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

//教材写法
void get_next(SString Str,int next[])
{
    int i=1,j=0;
    next[1]=0;

    while(i<Str.length)
    {
        if(j==0||Str.ch[i]==Str.ch[j])
            i++,j++,next[i]=j;
        else j=next[j];//往前找
    }
}

void get_next_val(SString Str,int next[],int nextval[])//可通过next数组直接求
{
    nextval[1]=0;
    for(int j=2;j<=Str.length;j++)
    {
        if(Str.ch[next[j]]==Str.ch[j])
            nextval[j]=nextval[next[j]];
        else nextval[j]=next[j];
    }
}

//教材写法
void get_next_val(SString Str,int nextval[])
{
    int i=1,j=0;
    nextval[1]=0;

    while(i<Str.length)
    {
        if(j==0||Str.ch[i]==Str.ch[j])
        {
            i++,j++;
            if(Str.ch[i]!=Str.ch[j])
                nextval[i]=j;
            else nextval[i]=nextval[j];

        }
        else j=nextval[j];//往前找
    }
}




int StrIndex_KMP(SString Str1,SString Str2,int next[])//定位操作
{
    int i=1,j=1;//分别指向Str1和Str2的第一个元素
    while(i<=Str1.length&&j<=Str2.length)
    {
        if(j==0||Str1.ch[i]==Str2.ch[j])//j==0时也需要
            i++,j++;
        else j=next[j];
    }
    if(j>Str2.length)
        return i-Str2.length;
    else return 0;
}


void Test()
{
    SString s1,s2;

    //char str1[]="abaabaabcabaabc";
    char str1[]="abaacaabcabaabc";
    char str2[]="abaabc";

    int next[MaxLen+1];
    int nextval[MaxLen+1];
    int nextval1[MaxLen+1];

    StrAssign(s1, str1);
    StrAssign(s2, str2);
    
    get_next(s2, next);
    get_next_val(s2,nextval);
    get_next_val(s2, next,nextval1);

    PrintSString(s1);
    PrintSString(s2);

    for(int i=1;i<=s2.length;i++)
        cout << next[i] << " ";
    cout << endl;

    for(int i=1;i<=s2.length;i++)
        cout << nextval[i] << " ";
    cout << endl;

    for(int i=1;i<=s2.length;i++)
        cout << nextval1[i] << " ";
    cout << endl;
    
    //nextval只是优化了next数组
    
    //cout << StrIndex_KMP(s1,s2,next) << endl;
    //cout << StrIndex_KMP(s1,s2,nextval) << endl;

    cout << StrIndex_KMP(s1,s2,nextval1) << endl;
   
}

int main()
{
    Test();
    return 0;
}