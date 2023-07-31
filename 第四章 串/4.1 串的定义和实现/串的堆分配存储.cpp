#include<iostream>

using namespace std;

#define MaxLen 255

typedef struct{
    char *ch;
    int length;
}HString;

void InitHString(HString &Str)
{
    Str.length=0;
    Str.ch=(char *)malloc((MaxLen+1)*sizeof(char));
}

void StrAssign(HString &Str,char str[])//赋值操作
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

void StrCopy(HString &Str1,HString Str2)//复制操作
{
    Str1=Str2;//结构体可直接赋值
}

bool StrEmpty(HString Str)//判空操作
{
    return Str.length==0;
}


int StrCompare(HString Str1,HString Str2)//比较操作
{//若Str1>Str2,返回值>0;若Str1=Str2,返回0,若Str1<Str2,返回值<0
    for(int i=1;i<=Str1.length&&i<=Str2.length;i++)
        if(Str1.ch[i]!=Str2.ch[i])
            return Str1.ch[i]-Str2.ch[i];
    return Str1.length-Str2.length;
}

int StrLength(HString Str)//求串长
{
    return Str.length;
}

bool SubString(HString &Sub,HString Str,int pos,int len)//求子串
{
    if(pos+len-1>Str.length)
        return false;
    
    for(int i=pos;i<pos+len;i++)
        Sub.ch[i-pos+1]=Str.ch[i];
    Sub.length=len;
    return true;
}


void StrConCat(HString Str1,HString Str2,HString &Str)//连接Str1,Str2至Str中
{
    if(Str1.length+Str2.length>MaxLen)
    {
        cout << "两串长度和超过最大长度,无法连接" << endl;
        return ;
    }

    Str.length=Str1.length+Str2.length;

    int pos=1;

    for(int i=1;i<=Str1.length;i++)
        Str.ch[pos++]=Str1.ch[i];
    
    for(int i=1;i<=Str2.length;i++)
        Str.ch[pos++]=Str2.ch[i];

}

int StrIndex(HString Str1,HString Str2)//定位操作
{
    int pos=1;
    int len1=StrLength(Str1),len2=StrLength(Str2);
    HString Subs;

    InitHString(Subs);

    while(pos<=len1-len2+1)
    {
        SubString(Subs, Str1, pos, len2);
        if(StrCompare(Subs, Str2)==0)
            return pos;
        else pos++;
    }
    return 0;//Str1中不存在与T相等的子串
}


void PrintHString(HString Str)
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

void ClearString(HString &Str)//清空数组
{
    Str.length=0;
}


void DestroyString(HString &Str)//销毁操作
{
    free(Str.ch);
}



void Test()
{
    HString s1,s2;
    InitHString(s1);
    InitHString(s2);

    cout << StrEmpty(s1) << endl;

    char str1[]="hhhhhhhhellohhh ";
    char str2[]="ell";



    StrAssign(s1, str1);
    StrAssign(s2, str2);
    
    cout << StrEmpty(s1) << endl;

    cout << StrCompare(s1, s2) << endl;

    cout << StrLength(s1) << " " << StrLength(s2) << endl;

    HString Subs,Cats;
    InitHString(Subs);
    InitHString(Cats);

    if(SubString(Subs, s1, 4,4)==false)
        cout << "查无此串" << endl;
    else PrintHString(Subs);

    StrConCat(s1, s2, Cats);

    PrintHString(Cats);

    //StrCopy(s1,s2);

    PrintHString(s1);

    PrintHString(s2);

    cout << StrIndex(s1,s2) << endl;

    ClearString(s1);

    PrintHString(s1);


    DestroyString(s1);
    DestroyString(s2);
    DestroyString(Subs);
    DestroyString(Cats);
}

int main()
{
    Test();
    return 0;
}